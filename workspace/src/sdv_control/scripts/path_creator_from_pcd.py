#!/usr/bin/env python3
"""
Script para crear rutas desde mapas PCD
1. Carga y visualiza el mapa PCD
2. Click izquierdo para agregar puntos
3. Click derecho para finalizar y guardar
4. Interpola automáticamente cada 0.1m
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import yaml
import sys
from pathlib import Path

# ============================================================================
# CONFIGURACIÓN - COPIA/PEGA TUS DIRECTORIOS AQUÍ
# ============================================================================
PCD_FILE = "/home/vanttec/maps/Inc_map/cloudSurf.pcd"
OUTPUT_YAML = "/home/vanttec/vanttec_sdv/workspace/src/sdv_control/config/waypoints_path.yaml"
# ============================================================================

def load_pcd(pcd_file):
    """Carga archivo PCD y retorna array numpy de puntos"""
    with open(pcd_file, 'r') as f:
        lines = f.readlines()
    
    # Encontrar donde empiezan los datos
    data_start = 0
    points_count = 0
    for i, line in enumerate(lines):
        if line.startswith('POINTS'):
            points_count = int(line.split()[1])
        if line.startswith('DATA'):
            data_start = i + 1
            break
    
    # Leer puntos
    points = []
    for line in lines[data_start:data_start + points_count]:
        values = line.strip().split()
        if len(values) >= 3:
            try:
                points.append([float(values[0]), float(values[1]), float(values[2])])
            except:
                continue
    
    return np.array(points)

def interpolate_path(waypoints, spacing=0.1):
    """Interpola waypoints cada 'spacing' metros"""
    if len(waypoints) < 2:
        return waypoints
    
    interpolated = []
    
    for i in range(len(waypoints) - 1):
        p1 = np.array(waypoints[i])
        p2 = np.array(waypoints[i + 1])
        
        dist = np.linalg.norm(p2 - p1)
        num_points = max(int(dist / spacing), 1)
        
        for j in range(num_points):
            t = j / num_points
            point = p1 + t * (p2 - p1)
            interpolated.append(point.tolist())
    
    interpolated.append(waypoints[-1])
    return interpolated

class PathCreator:
    def __init__(self, pcd_points):
        self.pcd_points = pcd_points
        self.path_points = []
        self.selection_mode = False  # Modo de selección desactivado al inicio
        
        self.fig = plt.figure(figsize=(14, 10))
        self.ax = self.fig.add_subplot(111)
        
        # Subsampling para visualización rápida
        subsample = max(1, len(pcd_points) // 50000)
        sampled_points = pcd_points[::subsample]
        
        # Vista 2D (X-Y)
        self.ax.scatter(sampled_points[:, 0], sampled_points[:, 1], 
                       c='dimgray', s=3, alpha=0.6, label='Mapa PCD')
        self.ax.set_xlabel('X (m)')
        self.ax.set_ylabel('Y (m)')
        self.update_title()
        self.ax.grid(True)
        self.ax.axis('equal')
        
        self.path_line, = self.ax.plot([], [], 'r-', linewidth=2, label='Path')
        self.path_dots = self.ax.scatter([], [], c='red', s=200, marker='o', 
                                        edgecolors='darkred', linewidths=3, label='Waypoints')
        self.ax.legend(loc='upper right')
        
        # Texto de ayuda en la esquina
        self.help_text = self.fig.text(0.02, 0.98, 
            'ESPACIO: Activar/Desactivar selección | U: Deshacer último punto | C: Limpiar todo',
            fontsize=10, verticalalignment='top', bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8))
        
        self.cid_click = self.fig.canvas.mpl_connect('button_press_event', self.on_click)
        self.cid_key = self.fig.canvas.mpl_connect('key_press_event', self.on_key)
    
    def update_title(self):
        mode_str = "SELECCIÓN ACTIVA" if self.selection_mode else "NAVEGACIÓN (zoom/pan)"
        color = 'green' if self.selection_mode else 'blue'
        self.ax.set_title(f'Modo: {mode_str} - Puntos: {len(self.path_points)}\n'
                         f'Click izq: agregar | Click der: finalizar | ESPACIO: cambiar modo',
                         color=color, fontweight='bold', fontsize=11)
    
    def on_key(self, event):
        if event.key == ' ':  # Barra espaciadora
            self.selection_mode = not self.selection_mode
            self.update_title()
            mode_text = "ACTIVADO" if self.selection_mode else "DESACTIVADO"
            print(f"\nModo selección: {mode_text}")
            if self.selection_mode:
                print("Ahora puedes hacer click para agregar waypoints")
            else:
                print("Usa las herramientas de navegación (zoom/pan) de la barra superior")
            self.fig.canvas.draw()
        
        elif event.key == 'u':  # Deshacer
            if len(self.path_points) > 0:
                removed = self.path_points.pop()
                print(f"Eliminado punto {len(self.path_points) + 1}: [{removed[0]:.2f}, {removed[1]:.2f}]")
                self.update_title()
                self.update_plot()
        
        elif event.key == 'c':  # Limpiar todo
            if len(self.path_points) > 0:
                self.path_points.clear()
                print("Todos los puntos eliminados")
                self.update_title()
                self.update_plot()
        
        elif event.key == 'enter':  # Finalizar con Enter
            if len(self.path_points) > 0:
                print(f"\nPath completado con {len(self.path_points)} waypoints")
                plt.close(self.fig)
        
    def on_click(self, event):
        if event.inaxes != self.ax:
            return
        
        # Solo procesar clicks si está en modo selección
        if not self.selection_mode:
            return
        
        if event.button == 1:  # Click izquierdo
            self.path_points.append([event.xdata, event.ydata, 0.0])
            print(f"Punto {len(self.path_points)}: [{event.xdata:.2f}, {event.ydata:.2f}, 0.0]")
            self.update_title()
            self.update_plot()
            
        elif event.button == 3:  # Click derecho
            if len(self.path_points) > 0:
                print(f"\nPath completado con {len(self.path_points)} waypoints")
                plt.close(self.fig)
    
    def update_plot(self):
        if len(self.path_points) > 0:
            points_array = np.array(self.path_points)
            self.path_dots.set_offsets(points_array[:, :2])
            
            if len(self.path_points) > 1:
                self.path_line.set_data(points_array[:, 0], points_array[:, 1])
            else:
                self.path_line.set_data([], [])
        else:
            self.path_dots.set_offsets(np.empty((0, 2)))
            self.path_line.set_data([], [])
        
        self.fig.canvas.draw()
    
    def get_path(self):
        return self.path_points

def save_path_yaml(waypoints, output_file):
    """Guarda waypoints en formato YAML"""
    path_data = {
        'frame_id': 'map',
        'waypoints': [
            {'x': float(p[0]), 'y': float(p[1]), 'z': float(p[2])}
            for p in waypoints
        ]
    }
    
    with open(output_file, 'w') as f:
        yaml.dump(path_data, f, default_flow_style=False)
    
    print(f"Path guardado en: {output_file}")
    print(f"Total de puntos interpolados: {len(waypoints)}")
def main():
    # Usar las variables configuradas al inicio del archivo
    pcd_file = Path(PCD_FILE)
    output_file = Path(OUTPUT_YAML)
    interpolation_spacing = 0.1
    
    # Permitir override por argumentos de línea de comandos
    if len(sys.argv) > 1:
        pcd_file = Path(sys.argv[1])
    if len(sys.argv) > 2:
        output_file = Path(sys.argv[2])
    
    if not pcd_file.exists():
        print(f"Error: No se encuentra el archivo PCD: {pcd_file}")
        print(f"\nEdita las variables al inicio del script:")
        print(f"  PCD_FILE = '{pcd_file}'")
        print(f"  OUTPUT_YAML = '{output_file}'")
        return
    
    print(f"Cargando mapa PCD: {pcd_file}")
    pcd_points = load_pcd(str(pcd_file))
    print(f"Puntos cargados: {len(pcd_points)}")
    
    print("\n" + "="*60)
    print("INSTRUCCIONES:")
    print("="*60)
    print("1. Usa las herramientas de la barra superior para navegar:")
    print("   - Zoom: Icono de lupa o rueda del mouse")
    print("   - Pan: Icono de cruz o click medio + arrastrar")
    print("\n2. Presiona BARRA ESPACIADORA para activar modo selección")
    print("\n3. Con selección activa:")
    print("   - Click izquierdo: agregar waypoint")
    print("   - Click derecho: finalizar y guardar")
    print("   - U: deshacer último punto")
    print("   - C: limpiar todos los puntos")
    print("   - ENTER: finalizar")
    print("\n4. Presiona ESPACIO de nuevo para volver a navegar")
    print("="*60 + "\n")
    
    creator = PathCreator(pcd_points)
    plt.show()
    
    raw_path = creator.get_path()
    
    if len(raw_path) == 0:
        print("No se creó ningún path")
        return
    
    print(f"\nInterpolando path cada {interpolation_spacing}m...")
    interpolated_path = interpolate_path(raw_path, interpolation_spacing)
    
    save_path_yaml(interpolated_path, output_file)
    
    # Visualización final
    raw_array = np.array(raw_path)
    interp_array = np.array(interpolated_path)
    
    fig, ax = plt.subplots(figsize=(10, 8))
    ax.scatter(pcd_points[::max(1, len(pcd_points)//30000), 0], 
              pcd_points[::max(1, len(pcd_points)//30000), 1],
              c='gray', s=0.5, alpha=0.3, label='Mapa')
    ax.plot(raw_array[:, 0], raw_array[:, 1], 'ro-', linewidth=3, 
           markersize=12, label=f'Waypoints originales ({len(raw_path)})')
    ax.plot(interp_array[:, 0], interp_array[:, 1], 'b.', markersize=2, 
           label=f'Path interpolado ({len(interpolated_path)} pts)')
    ax.set_xlabel('X (m)')
    
    ax.set_ylabel('Y (m)')
    ax.set_title('Path Final')
    ax.legend()
    ax.grid(True)
    ax.axis('equal')
    plt.show()

if __name__ == '__main__':
    main()

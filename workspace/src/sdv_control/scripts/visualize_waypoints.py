#!/usr/bin/env python3
"""
Visualizador rápido de waypoints sobre mapa PCD
"""

import numpy as np
import matplotlib.pyplot as plt
import yaml
import sys
from pathlib import Path

# ============================================================================
# CONFIGURACIÓN - COPIA/PEGA TUS DIRECTORIOS AQUÍ
# ============================================================================
PCD_FILE = "/home/vanttec/maps/Inc_map/cloudSurf.pcd"
YAML_FILE = "/home/vanttec/vanttec_sdv/workspace/src/sdv_control/config/waypoints_path.yaml"
# ============================================================================


def load_pcd(pcd_file):
    """Carga archivo PCD"""
    with open(pcd_file, 'r') as f:
        lines = f.readlines()
    
    data_start = 0
    points_count = 0
    for i, line in enumerate(lines):
        if line.startswith('POINTS'):
            points_count = int(line.split()[1])
        if line.startswith('DATA'):
            data_start = i + 1
            break
    
    points = []
    for line in lines[data_start:data_start + points_count]:
        values = line.strip().split()
        if len(values) >= 3:
            try:
                points.append([float(values[0]), float(values[1]), float(values[2])])
            except:
                continue
    
    return np.array(points)


def load_waypoints(yaml_file):
    """Carga waypoints desde YAML"""
    with open(yaml_file, 'r') as f:
        data = yaml.safe_load(f)
    
    waypoints = []
    for wp in data['waypoints']:
        waypoints.append([wp['x'], wp['y'], wp['z']])
    
    return np.array(waypoints)


def main():
    # Usar las variables configuradas al inicio del archivo
    yaml_file = Path(YAML_FILE)
    pcd_file = Path(PCD_FILE)
    
    # Permitir override por argumentos de línea de comandos
    if len(sys.argv) > 1:
        yaml_file = Path(sys.argv[1])
    if len(sys.argv) > 2:
        pcd_file = Path(sys.argv[2])
    
    # Cargar datos
    print(f"Cargando PCD: {pcd_file}")
    if not pcd_file.exists():
        print(f"Error: No existe {pcd_file}")
        print(f"\nEdita las variables al inicio del script:")
        print(f"  PCD_FILE = '{pcd_file}'")
        print(f"  YAML_FILE = '{yaml_file}'")
        return
    pcd_points = load_pcd(str(pcd_file))
    print(f"Puntos PCD: {len(pcd_points)}")
    
    print(f"Cargando waypoints: {yaml_file}")
    if not yaml_file.exists():
        print(f"Error: No existe {yaml_file}")
        return
    waypoints = load_waypoints(str(yaml_file))
    print(f"Waypoints: {len(waypoints)}")
    
    # Visualizar
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 8))
    
    # Vista completa
    subsample = max(1, len(pcd_points) // 50000)
    sampled = pcd_points[::subsample]
    
    ax1.scatter(sampled[:, 0], sampled[:, 1], c='gray', s=0.5, alpha=0.3, label='Mapa PCD')
    ax1.plot(waypoints[:, 0], waypoints[:, 1], 'r-', linewidth=2, label='Path')
    ax1.scatter(waypoints[:, 0], waypoints[:, 1], c='red', s=50, marker='o', 
               edgecolors='darkred', linewidths=2, label='Waypoints', zorder=5)
    ax1.scatter(waypoints[0, 0], waypoints[0, 1], c='green', s=200, marker='*', 
               edgecolors='darkgreen', linewidths=2, label='Inicio', zorder=6)
    ax1.scatter(waypoints[-1, 0], waypoints[-1, 1], c='blue', s=200, marker='s', 
               edgecolors='darkblue', linewidths=2, label='Final', zorder=6)
    ax1.set_xlabel('X (m)')
    ax1.set_ylabel('Y (m)')
    ax1.set_title(f'Vista completa - {len(waypoints)} waypoints')
    ax1.grid(True, alpha=0.3)
    ax1.axis('equal')
    ax1.legend()
    
    # Vista zoom en el path
    margin = 5
    x_min, x_max = waypoints[:, 0].min() - margin, waypoints[:, 0].max() + margin
    y_min, y_max = waypoints[:, 1].min() - margin, waypoints[:, 1].max() + margin
    
    mask = ((pcd_points[:, 0] >= x_min) & (pcd_points[:, 0] <= x_max) &
            (pcd_points[:, 1] >= y_min) & (pcd_points[:, 1] <= y_max))
    zoomed = pcd_points[mask]
    subsample_zoom = max(1, len(zoomed) // 30000)
    
    ax2.scatter(zoomed[::subsample_zoom, 0], zoomed[::subsample_zoom, 1], 
               c='gray', s=1, alpha=0.4, label='Mapa PCD')
    ax2.plot(waypoints[:, 0], waypoints[:, 1], 'r-', linewidth=2, label='Path')
    ax2.scatter(waypoints[:, 0], waypoints[:, 1], c='red', s=50, marker='o',
               edgecolors='darkred', linewidths=2, label='Waypoints', zorder=5)
    
    # Numerar algunos waypoints
    step = max(1, len(waypoints) // 10)
    for i in range(0, len(waypoints), step):
        ax2.annotate(str(i), (waypoints[i, 0], waypoints[i, 1]), 
                    xytext=(5, 5), textcoords='offset points', fontsize=8,
                    bbox=dict(boxstyle='round,pad=0.3', facecolor='yellow', alpha=0.7))
    
    ax2.scatter(waypoints[0, 0], waypoints[0, 1], c='green', s=200, marker='*',
               edgecolors='darkgreen', linewidths=2, label='Inicio', zorder=6)
    ax2.scatter(waypoints[-1, 0], waypoints[-1, 1], c='blue', s=200, marker='s',
               edgecolors='darkblue', linewidths=2, label='Final', zorder=6)
    
    ax2.set_xlabel('X (m)')
    ax2.set_ylabel('Y (m)')
    ax2.set_title('Vista zoom en el path')
    ax2.grid(True, alpha=0.3)
    ax2.axis('equal')
    ax2.legend()
    
    # Info
    distance = np.sum(np.linalg.norm(np.diff(waypoints[:, :2], axis=0), axis=1))
    fig.suptitle(f'Path: {len(waypoints)} puntos | Distancia total: {distance:.2f}m', 
                fontsize=14, fontweight='bold')
    
    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    main()

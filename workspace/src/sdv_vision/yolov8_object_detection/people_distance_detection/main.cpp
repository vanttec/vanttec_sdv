#include "main.h"

int main() {
    // Crea el objeto YoloPose y carga el modelo una sola vez fuera del bucle principal
    auto yolo = YoloPose();
    yolo.init("C:/Users/rprie/OneDrive/Documents/GitHub/vanttec_sdv/workspace/src/sdv_vision/yolov8_object_detection/people_distance_detection/__sampledata/yolov8n-pose.onnx");

    cv::VideoCapture cap(0); // Abre la cámara por defecto

    // Reduce la resolución de la cámara
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    if(!cap.isOpened()){  // Comprueba si se abrió correctamente
        std::cout << "Error al abrir la cámara" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while(true){
        cap >> frame; // Obtiene un nuevo frame de la cámara

        if(frame.empty()){
            std::cout << "Error al leer el frame" << std::endl;
            break;
        }

        yoloPose(frame, yolo); // Procesa el frame con YoloPose

        // Mueve cv::waitKey(1) aquí
        if(cv::waitKey(1) >= 0) break; // Si se presiona una tecla, se sale del bucle
    }

    return 0;
}

void yoloPose(cv::Mat &image, YoloPose &yolo) {
    auto result = yolo.detect(image);

    ImageTools::draw(result, image);
    ImageTools::show(image);
    // Mueve cv::waitKey(1) aquí
    cv::waitKey(1);
}

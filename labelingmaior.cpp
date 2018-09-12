#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects, nobjectsmaior;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

  // busca objetos com buracos presentes
  nobjects=0;
  nobjectsmaior=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
		// achou um objeto
		nobjects++;
		p.x=j;
		p.y=i;
		floodFill(image,p,nobjects);
		if(nobjects==255){       // Se já estiver esgotado os rótulos
			nobjectsmaior = nobjectsmaior + nobjects;			
			nobjects = 0;    // Recebe zero para reiniciar a contagem		
		}
		
		floodFill(image,p,50); // "Apagando bolha" colocando um valor diferente
	}
	
      }
  }
  cout << "A quantidade de bolhas é: " << nobjects + nobjectsmaior;
  imshow("image", image);
  imwrite("labelingmaior.png", image);
  waitKey();
  return 0;
  
}

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image;
	int largura, altura;
	int nobjects, nobjectsmaior;
	
	CvPoint p;
	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	if(!image.data){
	    std::cout << "imagem nao carregou corretamente\n";
    	return(-1);
  	}
	largura = image.size().width;
	altura = image.size().height;
	
	p.x = 0;
	p.y = 0;
	
	//removendo bolhas que estao na borda

	for (int i = 0; i<altura; i++ ){ // removendo bolhas das bordas verticais
		if (image.at<uchar>(i,0) == 255 ){ // se na primeira coluna existe objeto
			p.x = 0; // largura
			p.y = i; // altura
			floodFill(image,p,0);     // pintando essas bolhas de preto
			
		}else if(image.at<uchar>(i,largura-1) == 255 ) // se na ultima coluna existe objeto
		{
			p.x = largura-1;
			p.y = i; // altura
			floodFill(image,p,0);
		}
	}
	
	
	for (int j = 0; j<largura; j++ ){ // removendo bolhas das bordas horizontais
		if (image.at<uchar>(0,j) == 255 ){ // se na primeira linha existe objeto
			p.x = j; //largura
			p.y = 0;
			floodFill(image,p,0);
			
		}else if(image.at<uchar>(altura-1,j) == 255 ) // se na ultima linha existe objeto
		{
			p.x = j;
			p.y = altura-1;
			floodFill(image,p,0);
		}
	}	

	imwrite("sembolhasborda.png", image);

	//Contando bolhas	
	nobjects=0;
	nobjectsmaior=0;
	 for(int i=0; i<altura; i++){
	   for(int j=0; j<largura; j++){
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
		
		//floodFill(image,p,0); // "Apagando bolha" colocando o valor do fundo
	}
	
      }
  }
	cout << "Numero de objetos:" << nobjects;
 	imshow("image", image);
	imwrite("sembolhasbordarotulada.png", image);
	waitKey();
	return 0;

}



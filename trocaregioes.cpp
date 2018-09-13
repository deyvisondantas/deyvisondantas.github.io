#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image, trocaregioes;
	Mat quadrante1, quadrante2, quadrante3, quadrante4; // Matrizes auxiliares
	int x, y;

	image=imread("sanduiche.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data){
		cout << "Não abriu sanduiche.png" <<endl;
	}	

	//obtendo as dimensões da imagem
	x = image.size().width; // largura
	y = image.size().height; // altura

	// Definindos os quadrantes
        // Quadrante 1 - Esquerda superior
        // Quadrante 2 - Direita superior
        // Quadrante 3 - Esquerda inferior
        // Quadrante 4 - Direita inferior
        

        // Rect() - Ponto inicial e a quantidade que ele vai percorrer no x e y a partir do ponto inicial
	quadrante1 = image( Rect( 0 ,  0 , x/2, y/2 )).clone();  
	quadrante2 = image( Rect(x/2,  0 , x/2, y/2 )).clone();
	quadrante3 = image( Rect( 0 , y/2, x/2, y/2 )).clone();
	quadrante4 = image( Rect(x/2, y/2, x/2 ,y/2 )).clone();

	
	image.copyTo(trocaregioes);
	//Trocando os quadrantes e colococando numa nova imagem
	quadrante1.copyTo(trocaregioes(Rect(x/2, y/2, x/2 , y/2 )));	
	quadrante2.copyTo(trocaregioes(Rect( 0 , y/2, x/2 , y/2 )));
	quadrante3.copyTo(trocaregioes(Rect(x/2,  0 , x/2 , y/2 )));
	quadrante4.copyTo(trocaregioes(Rect( 0 ,  0 , x/2 , y/2 )));
	

	namedWindow("Janela-2", WINDOW_AUTOSIZE);
	imshow("Janela-2",trocaregioes);
	imwrite("trocaregioes.png",trocaregioes);
	
	waitKey();
	return 0;
}





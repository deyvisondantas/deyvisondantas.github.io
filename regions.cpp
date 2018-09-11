#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
	Mat image; 
	Vec3b val;
	int x1,y1,x2,y2; 			// Coordenadas dos pontos P1 e P2

	image = imread("sanduiche.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data){
		cout << "Nao abriu sanduiche.png" <<endl;
	}
	
	cout << "Por favor insira as coordenadas do ponto P1 (x,y)" << endl;
	cin >> x1;
       	cin >> y1;
	cout << "Por favor insira as coordenadas do ponto p2 (x,y)" << endl;
	cin >> x2;
	cin >> y2;

	for (int i = x1; i < x2; i++){
		for (int j = y1; j < y2; j++){ 
			image.at<uchar>(i,j)=(255 - image.at<uchar>(i,j));
		}				 // Gerando o negativo
	}

	namedWindow("Janela-1",WINDOW_AUTOSIZE); // Criando janela 
	imshow("Janela-1", image);   		 // Exibindo imagem gerada
	imwrite("negativo.png",image);		 // Salvando imagem
	waitKey();
	//return 0;


}

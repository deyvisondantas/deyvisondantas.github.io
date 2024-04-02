#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image, semBolhanaBorda;
	int largura, altura;
	int nobjects, nobjectsmaior, nobjectsComBuracos, nobjectsSemBuracos, noburacos;
	
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

	image.copyTo(semBolhanaBorda);	 // Copiando image para uma nova imagem, a qual será trabalhada
	for (int i = 0; i<altura; i++ ){ // removendo bolhas das bordas verticais
		if (image.at<uchar>(i,0) == 255 ){ // se na primeira coluna existe objeto
			p.x = 0; // largura
			p.y = i; // altura
			floodFill(semBolhanaBorda,p,0);     // pintando essas bolhas de preto
		}else if(image.at<uchar>(i,largura-1) == 255 ){ // se na ultima coluna existe objeto
			p.x = largura-1;
			p.y = i; // altura
			floodFill(semBolhanaBorda,p,0);
		}
	}
	for (int j = 0; j<largura; j++ ){ // removendo bolhas das bordas horizontais
		if (image.at<uchar>(0,j) == 255 ){ // se na primeira linha existe objeto
			p.x = j; //largura
			p.y = 0;
			floodFill(semBolhanaBorda,p,0);
		}else if(image.at<uchar>(altura-1,j) == 255 ){ // se na ultima linha existe objeto
			p.x = j;
			p.y = altura-1;
			floodFill(semBolhanaBorda,p,0);
		}
	}	
	imshow("semBolhanaBorda",semBolhanaBorda);
	imwrite("sembolhasborda.png", semBolhanaBorda);

	
	//Contando bolhas 
	nobjects=0;
	nobjectsmaior=0;
	for(int i=0; i<altura; i++){
		for(int j=0; j<largura; j++){
			if(semBolhanaBorda.at<uchar>(i,j) == 255){
				// achou um objeto
				nobjects++;
				p.x = j;
				p.y = i;
				floodFill(semBolhanaBorda,p,nobjects);
			
				if(nobjects == 255){       // Se já estiver esgotado os rótulos
					nobjectsmaior = nobjectsmaior + nobjects;			
					nobjects = 0;    // Recebe zero para reiniciar a contagem		
			
				}
				floodFill(semBolhanaBorda,p,50); // "Apagando bolha" colocando um valor diferente
			}		
		}
	}
	nobjects =  nobjects + nobjectsmaior; // Caso 'nobjectos' não chegue a 255 a partir da segunda contagem
	imshow("sembolhasbordarotulada",semBolhanaBorda);
	imwrite("sembolhasbordarotulada.png",semBolhanaBorda);
  


	// Contando bolhas com buracos e buracos
	noburacos = 0;
	nobjectsComBuracos = 0;	
	p.x = 0;  // Setando o primeiro pixel em p
	p.y = 0;
	floodFill(semBolhanaBorda,p,128); // Pintando fundo da imagem com 128
		

	for(int i = 0; i< altura; i++){
		for(int j = 0; j<largura; j++){
			if(semBolhanaBorda.at<uchar>(i,j) == 0){  // se for 0, é um buraco
				noburacos++;
				nobjectsComBuracos++;				
				p.x = j;
				p.y = i;
				floodFill(semBolhanaBorda,p,noburacos);  // rotulando buracos
			}
		}
	}
	imshow("buracosrotulados",semBolhanaBorda);
	imwrite("buracosrotulados.png",semBolhanaBorda);

	nobjectsSemBuracos =  nobjects - nobjectsComBuracos;	

	cout << "Numero de objetos que não estão na borda: " << nobjects << endl;;
	cout << "Numero de objetos sem buracos: " << nobjectsSemBuracos << endl;
	cout << "Numero de objetos com buracos: " << nobjectsComBuracos << endl;
	cout << "Numero de buracos: " << noburacos << endl;

 	//imshow("image", semborda);
	
	waitKey();
	return 0;

}



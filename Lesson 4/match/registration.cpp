#include <opencv/cv.h>    
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>    
#include <math.h>
#include <fstream>
#define PI 3.1415926
typedef  unsigned long uint32;  
typedef  unsigned int  uint16;  
typedef  unsigned char uint8;  
using namespace cv;
using namespace std;
   
IplImage *Dist; 
int height, width;
int pre_x;
uint8    TemplatePixelm10 = 0;  
uint8    TemplatePixelm01 = 0;  
uint8    TemplatePixeln01 = 0;  
uint8    TemplatePixeln10 = 0;  
uint8    TemplatePixelm1n1 = 0;  
uint8    TemplatePixelm1n0 = 0;  
uint8    TemplatePixelm0n1 = 0;  
uint8    TemplatePixelm0n0 = 0;  
  
void CalTemplateDist(IplImage* I,IplImage* Dist, long* Nb)    //������ģ��ͼ��Ӧλ���ϵľ���  
{  
    int i,j;  
    float dis;  
    for ( i=0; i<I->height; i++ )  
    {  
        uint8* ptr = (uint8*)( I->imageData + i*I->widthStep );  
        for ( j=0; j<I->width; j++ )  
        {  
            uint8 Pixel = ptr[j];  
            if(Pixel==0)  
            {  
                dis = 0;  
                (*Nb)++;  
            }  
            else  
            {  
                  
                if( i==0 && j==0 )                     //��һ�е�һ����  
                {  
                    TemplatePixelm10  = ptr[j+1];  
                    TemplatePixeln10  = *( I->imageData + (i+1)*I->widthStep + j );  
                    TemplatePixelm1n1 = *( I->imageData + (i+1)*I->widthStep + j+1 );  
                    if( TemplatePixelm10==0 || TemplatePixeln10==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm1n1==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else if( i==0 && j>0 && j<(I->width-1) )    //��һ��  
                {  
                    TemplatePixelm10  = ptr[j+1];  
                    TemplatePixelm01  = ptr[j-1];  
                    TemplatePixeln10  = *( I->imageData + (i+1)*I->widthStep + j );  
                    TemplatePixelm1n1 = *( I->imageData + (i+1)*I->widthStep + j+1 );  
                    TemplatePixelm0n1 = *( I->imageData + (i+1)*I->widthStep + j-1 );  
                    if( TemplatePixelm10==0 || TemplatePixeln10==0 || TemplatePixelm01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm1n1==0 || TemplatePixelm0n1==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }   
                else if( i==0 && j==(I->width-1) )           //��һ�����һ����  
                {     
                    TemplatePixelm01  = ptr[j-1];  
                    TemplatePixeln10  = *( I->imageData + (i+1)*I->widthStep + j );  
                    TemplatePixelm0n1 = *( I->imageData + (i+1)*I->widthStep + j-1 );  
                    if( TemplatePixeln10==0 || TemplatePixelm01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm0n1==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else if( j==0 && i>0 && i<(I->height-1) )    //��һ��  
                {  
                    TemplatePixelm10  = ptr[j+1];  
                    TemplatePixeln01  = *( I->imageData + (i-1)*I->widthStep + j );  
                    TemplatePixeln10  = *( I->imageData + (i+1)*I->widthStep + j );  
                    TemplatePixelm1n1 = *( I->imageData + (i+1)*I->widthStep + j+1 );  
                    TemplatePixelm1n0 = *( I->imageData + (i-1)*I->widthStep + j+1 );  
                    if( TemplatePixelm10==0 || TemplatePixeln10==0 || TemplatePixeln01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm1n1==0 || TemplatePixelm1n0==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else if( i>0 && i<(I->height-1) && j==(I->width-1) )     //���һ��  
                {     
                    TemplatePixelm01  = ptr[j-1];  
                    TemplatePixeln01  = *( I->imageData + (i-1)*I->widthStep + j );  
                    TemplatePixeln10  = *( I->imageData + (i+1)*I->widthStep + j );  
                    TemplatePixelm0n1 = *( I->imageData + (i+1)*I->widthStep + j-1 );  
                    TemplatePixelm0n0 = *( I->imageData + (i-1)*I->widthStep + j-1 );  
                    if( TemplatePixeln10==0 || TemplatePixelm01==0 || TemplatePixeln01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm0n1==0 || TemplatePixelm0n0==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else if( j==0 && i==(I->height-1) )    //���һ�����һ����  
                {  
                    TemplatePixelm10  = ptr[j+1];  
                    TemplatePixeln01  = *( I->imageData + (i-1)*I->widthStep + j );  
                    TemplatePixelm1n0 = *( I->imageData + (i-1)*I->widthStep + j+1 );  
                    if( TemplatePixelm10==0 || TemplatePixeln01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm1n0==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else if( j>0 && j<(I->width-1) && i==(I->height-1) )    //���һ��  
                {  
                    TemplatePixelm10  = ptr[j+1];  
                    TemplatePixelm01  = ptr[j-1];  
                    TemplatePixeln01  = *( I->imageData + (i-1)*I->widthStep + j );     
                    TemplatePixelm1n0 = *( I->imageData + (i-1)*I->widthStep + j+1 );  
                    TemplatePixelm0n0 = *( I->imageData + (i-1)*I->widthStep + j-1 );  
                    if( TemplatePixelm10==0 || TemplatePixeln01==0 || TemplatePixelm01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm1n0==0 || TemplatePixelm0n0==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else if( j==(I->width-1) && i==(I->height-1) )    //���һ�����һ����  
                {  
                      
                    TemplatePixelm01  = ptr[j-1];  
                    TemplatePixeln01  = *( I->imageData + (i-1)*I->widthStep + j );                     
                    TemplatePixelm0n0 = *( I->imageData + (i-1)*I->widthStep + j-1 );  
                    if( TemplatePixeln01==0 || TemplatePixelm01==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm0n0==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
                else  
                {  
                    TemplatePixelm10  = ptr[j+1];  
                    TemplatePixelm01  = ptr[j-1];  
                    TemplatePixeln01  = *( I->imageData + (i-1)*I->widthStep + j );  
                    TemplatePixeln10  = *( I->imageData + (i+1)*I->widthStep + j );  
                    TemplatePixelm1n0 = *( I->imageData + (i-1)*I->widthStep + j+1 );  
                    TemplatePixelm0n0 = *( I->imageData + (i-1)*I->widthStep + j-1 );  
                    TemplatePixelm1n1 = *( I->imageData + (i+1)*I->widthStep + j+1 );  
                    TemplatePixelm0n1 = *( I->imageData + (i+1)*I->widthStep + j-1 );  
                    if( TemplatePixeln01==0 || TemplatePixelm01==0 || TemplatePixelm10==0 || TemplatePixeln10==0 )  
                        dis = 0.3;  
                    else if( TemplatePixelm0n0==0 || TemplatePixelm1n0==0 || TemplatePixelm0n1==0 || TemplatePixelm1n1==0 )  
                        dis = 0.7;  
                    else  
                        dis = 1;  
                }  
  
            }  
            *(Dist->imageData + i*Dist->widthStep + j) = (uint8)(dis*255);  
              
        }  
  
    }  
  
}  
void dist_match(IplImage *src_img, IplImage* Dist,double MinMatch, CvPoint* pt, long* Na, long* Nb)  //����ƥ��  
{  
    int i,j,m,n;  
    double SigmaGT;  
    uint8 SrcValue;  
    double DistValue;  
    double Match;  
      
  
    for ( i=Dist->height/2; i<(src_img->height - Dist->height/2); i++ )  
    {          
        SigmaGT = 0;  
        *Na = 0;  
        for( m=0; m<Dist->height; m++ )  
        {  
            for( n=0; n<Dist->width; n++ )  
            {  
				SrcValue  = *( src_img->imageData + (i-Dist->height/2+m)*src_img->widthStep + pre_x-Dist->width/2+n );    
                if(SrcValue==0)  
                {  
                    DistValue = (double)*( Dist->imageData +m*Dist->widthStep + n )/255;  
                    SigmaGT += DistValue;  
                    (*Na)++;  
                }  
            }  
        }  
  
        if( (*Na) > (*Nb) )  
        {  
            Match = ( SigmaGT + (*Na) - (*Nb) )/( (*Na) + (*Nb) );  
        }  
        else  
        {  
            Match = ( SigmaGT + (*Nb) - (*Na) )/( (*Na) + (*Nb) );  
        }  
  
        if( Match < MinMatch )  
        {  
            MinMatch = Match;                //����ƥ�����Сֵ����ƥ���λ��  
            pt->x = pre_x;  
            pt->y = i;  
        }   
  
    }  
  
} 

void convert_coordinate(float &x, float &y)
{
    //int width = (*src).width;
    //int height = (*src).height;

    x = x*(2*PI)/width;
    //y = y*PI/height-(PI/2.0);  //-90~90
	y = y*PI/height;
	////����
    //if(y > 0.0)
    //{
    //  y = (PI/2.0) - y;
    //}else
    //{
    //  y = -(PI/2.0) - y;
    //}   
}

/*
*argv1:����׼��ԭʼͼ��
*argv2:ģ��ͼ��
*argv3:ԭʼͼ���canny��Եͼ
*argv4:ģ��ͼ���canny��Եͼ
*argv5:����λ��
*argv6:ƥ��λ�ñ�����ı��ļ���
*argv7:ƥ����ͼƬ����·��
*/
int main(int argc ,char *argv[])  
{  
    IplImage* src_img, *temp_img;                                 //�������  
    double MinMatch = 2000;  
    CvPoint MatchPoint = cvPoint(1,1);  
    long Na=0,Nb=0;                                                     //����0�ĸ���  
    src_img  = cvLoadImage(argv[1],0);                 //��������ͼ  
    temp_img = cvLoadImage(argv[2],0);  
	IplImage *paint = cvLoadImage(argv[1], 1);

	height = src_img->height;
	width = src_img->width;
	pre_x = atoi(argv[5]);

	//��ȡ����
	Mat srcimg = cv::cvarrToMat(src_img);
	Mat tempimg = cv::cvarrToMat(temp_img);
	Mat src_edge, temp_edge;
	
	//blur �Ҷ�ͼƬ
    blur(srcimg, srcimg, Size(3,3));
	blur(tempimg, tempimg, Size(3,3));

	// Canny ��Ե���
    Canny(srcimg, src_edge, 10, 30, 3);
	Canny(tempimg, temp_edge, 10, 30, 3);
	imwrite(argv[3],src_edge);
	imwrite(argv[4],temp_edge);

      
    Dist = cvCreateImage(cvGetSize(temp_img),IPL_DEPTH_8U,1);  
    IplImage I = temp_edge;
    CalTemplateDist(&I, Dist, &Nb);  
	IplImage img = src_edge;
    dist_match(&img, Dist, MinMatch, &MatchPoint, &Na, &Nb);  
    printf("%d,%d\n", MatchPoint.x, MatchPoint.y);
    cvRectangle(paint, cvPoint(MatchPoint.x-100,MatchPoint.y-100), cvPoint(MatchPoint.x+100, MatchPoint.y+100), cvScalar(0, 0, 255), 3,8,0);  
    
	ofstream file(argv[6]);
	float x = MatchPoint.x;
	float y = MatchPoint.y;
    convert_coordinate(x, y);
    file<< x<<','<<y<<endl;
	cvSaveImage(argv[7], paint);
	   
    cvReleaseImage(&src_img);    
    cvReleaseImage(&temp_img); 
	cvReleaseImage(&paint);   
  
    return 0;  
}  
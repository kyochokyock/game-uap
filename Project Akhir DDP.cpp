//Tugas akhir UAP Kelompok 8
//
//Faras Raditia Maulana (2357051020)
//Muhammad Ghozi Pratama (2317051041)
//Azmi Hanifah (2317051028)

#include <iostream>				//Input Output perintah cout, cin, endl.
#include <conio.h>				//Digunakan untuk penggunaan fungsi getche.
#include <direct.h>				//Digunakan untuk fungsi fungsi terkait direktori
#include <stdlib.h>				//Mengandung fungsi-fungsi umum, seperti alokasi memori dinamis.
#include <string.h>				//Mengandung fungsi-fungsi untuk manipulasi string.
#include <windows.h>			//Digunakan untuk fungsi sleep.
#include <time.h>				//Digunakan untuk mengakses fungsi-fungsi terkait waktu.
#include <fstream>				//Digunakan untuk melakukan operasi input/output pada file.

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos = 6;
int score = 0;

void gotoxy(int x, int y)	//Fungsi ini digunakan untuk memindahkan kursor ke posisi tertentu di layar.
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)	//Fungsi ini mengatur tampilan kursor di layar.
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder(){		//untuk menggambar batas layar permainan.
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"=";
		gotoxy(i,SCREEN_HEIGHT); cout<<"=";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"|";
		gotoxy(SCREEN_WIDTH,i); cout<<"|";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"|";
	}
}
void genPipe(int ind){		//Menghasilkan posisi acak untuk celah di antara pipa.
	gapPos[ind] = 3 + rand()%14; 
}
void drawPipe(int ind){		//Digunakan untuk menggambar pipa pada layar.
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***"; 
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***"; 
		}
	} 
}
void erasePipe(int ind){	//Untuk menghapus pipa dari layar.
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
	}
}

void drawBird(){	//Untuk menggambar karakter burung pada layar.
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<bird[i][j];
		}
	}
}
void eraseBird(){	//Untuk menghapus karakter burung dari layar.
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<" ";
		}
	}
}

int collision(){	//Memeriksa apakah terjadi tabrakan antara burung dan pipa.
	if( pipePos[0] >= 61  ){
		if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){

			return 1;
		}
	}
	return 0;
}

void gameover(){	//Fungsi ini menampilkan pesan game over dan menunggu input sebelum kembali ke menu.
	system("cls");
		ifstream myfile;
	char sv_text;
	
	myfile.open("gameover.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	cout<<endl;
	gotoxy(49,14); cout<<"--------------------------";
	gotoxy(49,15); cout<<"-------- Game Over -------";
	gotoxy(49,16); cout<<"--------------------------";
	gotoxy(45,28); cout<<" Tekan Tombol apapun untuk kembali.";
	getch();
}
void updateScore(){		//Fungsi ini mengupdate dan menampilkan skor saat bermain.
	gotoxy(WIN_WIDTH + 7, 10);cout<<"Skor: "<<score<<endl;
}

void Profile1(){	//biodata anggota
	system("cls");
	
	ifstream myfile;	//digunakan untuk memanggil file dari luar yang sudah dibuat
	char sv_text;
	
	myfile.open("profile1image.txt", ios::app); //sesuaikan dengan nama file yang akan dipanggil
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	gotoxy(28,9); cout<<"------------------------------------------------------------";
	gotoxy(28,10); cout<<"Nama : Faras";
	gotoxy(28,11); cout<<"Umur : Gaada yang tau";
	gotoxy(28,12); cout<<"Tinggi : Relatif sih";
	gotoxy(28,13); cout<<"Passion : Nomor dua Prabowo-Gibran";
	gotoxy(28,14); cout<<"Cita - Cita : Detektif & Model";
	gotoxy(28,16); cout<<"Ga takut kegelapan, Karena kegelapan adalah diriku sendiri";
	gotoxy(28,17); cout<<"------------------------------------------------------------";
	gotoxy(41,28); cout<<"Tekan Tombol apapun untuk kembali.";
	getch();
}

void Profile2(){	
	system("cls");
	
	ifstream myfile;
	char sv_text;
	
	myfile.open("profile2image.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	gotoxy(42,9); cout<<"-----------------------------";
	gotoxy(42,10); cout<<"P lur, gwe goji";
	gotoxy(42,11); cout<<"gw suka loncat";
	gotoxy(42,12); cout<<"jangan percaya biografi 3";
	gotoxy(42,13); cout<<"-----------------------------";
	gotoxy(41,28); cout<<"Tekan Tombol apapun untuk kembali.";
	getch();
}

void Profile3(){	
	system("cls");
	
	ifstream myfile;
	char sv_text;
	
	myfile.open("profile3image.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	gotoxy(37,9); cout<<"------------------------------------------";
	gotoxy(37,10); cout<<"Biasa dipanggil Azmii";
	gotoxy(37,11); cout<<"hobi saya ngoding dan stalking";
	gotoxy(37,12); cout<<"dikelompok ini saya anggota paling rajin";
	gotoxy(37,13); cout<<"------------------------------------------";
	gotoxy(41,28); cout<<"Tekan Tombol apapun untuk kembali.";
	getch();
}

void credit(){ //menu credit
	
	do {
	system("cls");
	ifstream myfile;
	char sv_text;
	
	myfile.open("creditimage.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	gotoxy(2,1); cout<<"Kredit";
	gotoxy(2,2); cout<<"---------------*";
	gotoxy(2,4); cout<<"Disclaimer :3";
	gotoxy(2,6); cout<<"Untuk sistem dari game ini kami masih menggunakan contoh "; 
	gotoxy(2,7); cout<<"dari pihak lain, yaitu dari -AngularsCoding, namun beberapa ";
	gotoxy(2,8); cout<<"sistem dari game ini kami modifikasi sedemikian rupa ";
	gotoxy(2,9); cout<<"untuk mengembangkan game ini ke versi yang lebih baik";
	gotoxy(2,10); cout<<"-----------------------------------------------------------*";
	gotoxy(2,12); cout<<"Beberapa source yang kami gunakan pada game ini";
	gotoxy(2,14); cout<<"https://github.com/AngularsCoding";
	gotoxy(2,15); cout<<"https://chat.openai.com/";
	gotoxy(2,16); cout<<"https://www.asciiart.eu/";
	gotoxy(2,17); cout<<"--------------------------------------------------*";
	gotoxy(2,19); cout<<"Anggota Kelompok 8 (Tekan 1,2, atau 3 untuk melihat biografi anggota)";
	gotoxy(2,21); cout<<"1. Faras Raditia Maulana";
	gotoxy(2,22); cout<<"2. Muhammad Ghozi Pratama";
	gotoxy(2,23); cout<<"3. Azmii Haniifah";
	gotoxy(2,24); cout<<"4. Cabut";
	gotoxy(2,25); cout<<"----------------------------*";
	char op = getche();
	
	if( op=='1') Profile1();
		else if( op=='2') Profile2();
		else if( op=='3') Profile3();
		else if( op=='4') return;
	
	}while(1);
}
	
void instructions(){	//Fungsi ini menampilkan instruksi permainan.
	system("cls");
	
	ifstream myfile;
	char sv_text;
	
	myfile.open("instructionimage.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	gotoxy(7,7); cout<<"Instruksi";
	gotoxy(7,9); cout<<"----------------";
	gotoxy(7,10); cout<<"Tekan Spasi untuk membuat burunk terbang";
	gotoxy(7,12); cout<<"Setiap kali pemain berhasil melewati satu pasang pipa, skor pemain bertambah.";
	gotoxy(7,13); cout<<"Jangan sampe burunk lu nabrak atau nyungsep ke tanah";
	gotoxy(7,14); cout<<"sakit soalnya.";
	gotoxy(41,28); cout<<"Tekan Tombol apapun untuk kembali";
	getch();
}

void play(){	//Fungsi utama untuk menjalankan permainan.
	
	system("color 60");
	birdPos = 6;	// Menginisialisasi posisi awal burung, skor, dan beberapa variabel pipa.
	score = 0;
	pipeFlag[0] = 1; 
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;
	
	system("cls");		// Membersihkan layar konsol.
	
	ifstream myfile;
	char sv_text;
	
	myfile.open("playimage.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	drawBorder();		// Menggambar batas layar dan pipa pertama.
	genPipe(0);
	updateScore();
	
	gotoxy(WIN_WIDTH + 5, 7);cout<<"CLOUD HOPPER";
	gotoxy(WIN_WIDTH + 6, 9);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 11);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 17);cout<<" Kontrol ";
	gotoxy(WIN_WIDTH + 6, 18);cout<<"---------";
	gotoxy(WIN_WIDTH + 2, 19);cout<<"  Spasi = loncat";
	
	gotoxy(20, 11);cout<<"Tekan Tombol apapun untuk mulai";	// Menunggu pemain menekan tombol apa pun untuk memulai permainan.
	getch();
	gotoxy(20, 11);cout<<"                               "; //menghilangkan tulisan start sebelum input untuk memulai permainan
	
	while(1){
		 
		if(kbhit()){	// Memeriksa apakah ada input dari keyboard.
			char ch = getch();	// Jika tombol spasi ditekan, burung melompat ke atas.
			if(ch==32){
				if( birdPos > 3 )
					birdPos-=3;
			} 
			if(ch==27){
				break;
			}
		}
		
		drawBird();
		drawPipe(0);
		drawPipe(1);
		if( collision() == 1 ){		// Memeriksa apakah terjadi tabrakan antara burung dan pipa.
			gameover();		// Jika tabrakan terdeteksi, memanggil fungsi gameover() dan mengakhiri permainan.
			return;
		}
		Sleep(100);		//Delay 0,1 detik.
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;	// Menyesuaikan posisi burung.
		
		if( birdPos > SCREEN_HEIGHT - 2 ){	
			gameover();
			return;
		}
		
		if( pipeFlag[0] == 1 )	// Memindahkan pipa ke kiri.
			pipePos[0] += 2;
		
		if( pipeFlag[1] == 1 )
			pipePos[1] += 2;
		
		if( pipePos[0] >= 40 && pipePos[0] < 42 ){
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if( pipePos[0] > 68 ){	// Jika pipa pertama mencapai posisi tertentu di layar, mengupdate skor.
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}
		
	}
	 
}

int main(){		//Fungsi utama program yang menangani tampilan menu dan memanggil fungsi play dan instructions berdasarkan input pengguna.
	system("color 60");
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	
	ifstream myfile;
	char sv_text;
	
	myfile.open("welcome.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
	gotoxy(0,28); cout<<"Meluncurrr.....";
	for(int i=0;i<115;i++){
	gotoxy(i,29); cout<<">";
	Sleep(50);
}
	
	
	do{
		system("cls");
		ifstream myfile;
	char sv_text;
	
	myfile.open("menuimage.txt", ios::app);
	
	if (!myfile.fail()){
		
		while(!myfile.eof()){
			myfile.get(sv_text);
			cout << sv_text;			
		}
		myfile.close();
	}
	
		gotoxy(36,12); cout<<" 	||		  # Menu # 		 ||";
		gotoxy(36,13); cout<<" 	||					 ||";
		gotoxy(36,14); cout<<" 	||		 1. Main		 ||";
		gotoxy(36,15); cout<<" 	||		 2. Instruksi	    	 ||";	 
		gotoxy(36,16); cout<<" 	||		 3. Kredit		 ||";
		gotoxy(36,17); cout<<" 	||		 4. Cabut		 ||";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') credit();
		else if( op=='4') exit(0);
		
	}while(1);
	
	return 0;
}


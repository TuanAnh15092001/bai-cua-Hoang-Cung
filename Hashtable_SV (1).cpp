//=====================================
/*                                   ||
Ho ten: Vu Ngoc Hoang Cung           ||
MSSV: 2001206991                     ||
Noi dung: Bai tap thuc hanh buoi 8   ||
*///                                 ||										
//=====================================

//====================================
#include <stdio.h>//                ||
#include <conio.h>//                ||
#include <iostream>//               ||
#include <stdlib.h>//               ||
#include <Windows.h>//              ||
//====================================

//====================================
#define _CRT_SECURE_NO_WARNINGS//   ||
#define TRUE 1//                    ||
#define FALSE 0//                   ||
#define MAXSIZE 101//               ||
//====================================
struct SinhVien{
	char MSSV[11], hoTen[51];
	int namSinh, diemSo;
};
//==================================================================
struct HashNode{
	SinhVien key;
	HashNode* next;
};
//==================================================================
typedef SinhVien Itemtype;
typedef HashNode* NodePtf;
//==================================================================
NodePtf bucket[MAXSIZE];
//==================================================================
void initBucket();
void createBRTreeFromFile();
int HashFunction(int key);
int isEmptyBucket(int b);
void Push(int b, Itemtype x);
void insertAfter(NodePtf p, Itemtype k);
void Place(int b, Itemtype k);
int isEmpty();
void insert(Itemtype k);
void freeNode(NodePtf p);
int Pop(int b);
int deleteAfter(NodePtf p);
void Remove(Itemtype k);
void clearBucket(int b);
void clear();
void traverseBucket(int b);
void Traverse();
void printGoodStudent();
NodePtf Search(Itemtype k);
void Menu();
void Process();
//==================================================================
void main(){
	Process();
	_getch();
}
//==================================================================
void Menu(){
	printf("\n ============================================================================");
	printf("\n ||----------------------------- Hash Table -------------------------------||");
	printf("\n ||************************************************************************||");
	printf("\n || 1. Khoi tao Hashtalbe tu file                                          ||");
	printf("\n || 2. Xuat Hashtable                                                      ||");	
	printf("\n || 3. Xuat nhung sinh vien xep loai gioi                                  ||");	
	printf("\n || 4. Xoa nhung sinh vien co x diem                                       ||");	
	printf("\n || 5. Xoa Hashtable                                                       ||");
	printf("\n || 0. Thoat chuong trinh                                                  ||");
	printf("\n ============================================================================\n");
}
//==================================================================
void Process(){
	int chon;
	Itemtype x;
	do{
		Menu();
		printf(" Nhap yeu cau: ");
		scanf("%d", &chon);
		switch(chon){
			case 0: exit(1);
				break;
			case 1:
				createBRTreeFromFile();
				printf(" Khoi tao Hashtable tu file thanh cong!");
					break;
			case 2:
				printf("\n Hashtable");
				Traverse();
					break;
			case 3:
				printf(" Nhung sinh vien xep loai gioi la: \n");
				printGoodStudent();
					break;
			case 4:
				printf(" Nhap diem can xoa: ");
				scanf("%d", &x.diemSo);
				while(Search(x)){
					Remove(x);
				}
				printf("\n Hashtable sau khi xoa nhung sinh vien co %d diem la: ", x.diemSo);
				Traverse();
				break;
			case 5:
				clear();
				printf(" Xoa hashtable thanh cong!");
					break;
			default: printf(" Vui long nhap lai!");
				break;
		}
	}while(chon != 0);
}   
//==================================================================
void initBucket(){
	for(int b = 0; b < MAXSIZE; b++)
		bucket[b] = NULL;
}
//==================================================================
void createBRTreeFromFile(){
	FILE *f;
	f = fopen("SinhVien.txt","rt");
	if(!f) return;
	int n;
	fscanf(f, "%d", &n);
	Itemtype x;
	for(int i = 0; i < n; i++){
		fscanf(f, "%s", &x.MSSV);
		fscanf(f, "%s", &x.hoTen);
		fscanf(f, "%d", &x.namSinh);
		fscanf(f, "%d", &x.diemSo);
		insert(x);
	}
	fclose(f);
}
//==================================================================
int HashFunction(int key){
	return key % MAXSIZE;
}
//==================================================================
int isEmptyBucket(int b){
	return (bucket[b] == NULL ? TRUE : FALSE);
}
//==================================================================
void Push(int b, Itemtype x){
	NodePtf p = new HashNode;
	if(!p)
		return;
	p->key = x;
	p->next = bucket[b];
	bucket[b] = p;
}
//==================================================================
void insertAfter(NodePtf p, Itemtype k){
	if(p == NULL)
		printf(" Khong them vao Node moi duoc!");
	else{
		NodePtf q = new HashNode;
		q->key = k;
		q->next = p->next;
		p->next = q;
	}
}
//==================================================================
void Place(int b, Itemtype k){
	NodePtf p, q;
	q = NULL;
	for(p = bucket[b]; p != NULL && k.diemSo > p->key.diemSo; p = p->next){
		q = p;
	}
	if(q == NULL)
		Push(b,k);
	else
		insertAfter(q,k);
}
//==================================================================
int isEmpty(){
	for(int b = 0; b < MAXSIZE; b++)
		if(bucket[b] != NULL)
			return FALSE;
	return TRUE;
}
//==================================================================
void insert(Itemtype k){
	int b = HashFunction(k.diemSo);
	Place(b,k);
}
//==================================================================
void freeNode(NodePtf p){
	delete p;
}
//==================================================================
int Pop(int b){
	NodePtf p;
	Itemtype k;
	if(isEmptyBucket(b)){
		printf(" Bucket %d bi rong, khong xoa duoc!", b);
		return FALSE;
	}
	p = bucket[b];
	k = p->key;
	bucket[b] = p->next;
	freeNode(p);
	return k.diemSo;
}
//==================================================================
int deleteAfter(NodePtf p){
	NodePtf q;
	Itemtype k;
	if( p == NULL|| p->next == NULL){
		printf("\n Xoa khong thanh cong!");
		return FALSE;
	}
	q = p->next;
	k = q->key;
	p->next = q->next;
	freeNode(q);
	return k.diemSo;
}
//==================================================================
void Remove(Itemtype k){
	NodePtf q, p;
	int b = HashFunction(k.diemSo);
	p = bucket[b];
	while(p != NULL && p->key.diemSo != k.diemSo){
		q = p;
		p = p->next;
	}
	if(p == NULL)
		printf("\n Sinh vien co %d diem khong ton tai!\n", k.diemSo);
	else if(p == bucket[b]){
		Pop(b);
		printf("\n Xoa sinh vien co %d diem thanh cong!\n", k.diemSo);
	}
	else{
		deleteAfter(q);
		printf("\n Xoa sinh vien co %d diem thanh cong!\n", k.diemSo);
	}
}
//==================================================================
void clearBucket(int b){
	NodePtf p, q;
	q = NULL;
	p = bucket[b];
	while(p != NULL){
		q = p;
		p = p ->next;
		freeNode(q);
	}
	bucket[b] = NULL;
}
//==================================================================
void clear(){
	for(int b = 0; b < MAXSIZE; b++)
		clearBucket(b);
}
//==================================================================
void traverseBucket(int b){
	NodePtf p = bucket[b];
	while(p != NULL){
		printf(" [%s, %s, %d, %d] -> ", p->key.MSSV, p->key.hoTen, p->key.namSinh, p->key.diemSo);
		p = p->next;
		if(!p)
			printf("NULL");
	}
}
//==================================================================
void Traverse(){
	for(int b = 0; b <= MAXSIZE; b++){
		printf("\n Bucket thu %d: ", b);
		traverseBucket(b);
	}
}
//==================================================================
NodePtf Search(Itemtype k){
	int b = HashFunction(k.diemSo);
	NodePtf p = bucket[b];
	while((p != NULL) && ( k.diemSo > p->key.diemSo)){
		p = p->next;
	}
	if(p == NULL || k.diemSo != p->key.diemSo){
		return NULL;
	}
	else{
		return p;
	}
}
//==================================================================
void printGoodStudent(){
	for(int b = MAXSIZE; b > 90; b--){
		traverseBucket(b);
	}
}
//==================================================================

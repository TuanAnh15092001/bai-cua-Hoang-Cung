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
#define MAXSIZE 10//                ||
//====================================

struct HashNode{
	int key;
	HashNode* next;
};

typedef HashNode* NodePtf;

NodePtf bucket[MAXSIZE];
//==================================================================
void initBucket();
int HashFunction(int key);
int isEmptyBucket(int b);
void Push(int b, int x);
void insertAfter(NodePtf p, int k);
void Place(int b, int k);
int isEmpty();
void insert(int k);
void freeNode(NodePtf p);
int Pop(int b);
int deleteAfter(NodePtf p);
void Remove(int k);
void clearBucket(int b);
void clear();
void traverseBucket(int b);
void Traverse();
NodePtf Search(int k);
void menu();
void thucThi();
//==================================================================
void main(){
	thucThi();
	_getch();
}
//==================================================================
void menu(){
	printf("\n ============================================================================");
	printf("\n ||----------------------------- Hash Table -------------------------------||");
	printf("\n ||************************************************************************||");
	printf("\n || 1. Khoi tao Hashtalbe                                                  ||");
	printf("\n || 2. Xuat Hashtable                                                      ||");
	printf("\n || 3. Them 1 khoa vao Hashtable                                           ||");
	printf("\n || 4. Xoa 1 khoa trong Hashtable                                          ||");
	printf("\n || 5. Tim kiem mot khoa co ton tai trong Hashtable hay khong              ||");
	printf("\n || 6. Xoa 1 bucket bat ki                                                 ||");
	printf("\n || 7. Xoa Hashtable                                                       ||");
	printf("\n || 0. Thoat chuong trinh                                                  ||");
	printf("\n ============================================================================\n");
}
//==================================================================
void thucThi(){
	HashNode *p;
	int n , k, b, chon;
	do{
		menu();
		printf(" Nhap yeu cau: ");
		scanf("%d", &chon);
		switch(chon)
		{
			case 0: exit(1);
				break;
			case 1:
				printf(" Nhap so luong phan tu can them vao Hashtable: ");
				scanf("%d", &n);
				for(int i = 0; i < n; i++){
					printf(" Nhap phan tu thu %d: ", i);
					scanf("%d", &k);
					insert(k);
				}
				break;
			case 2:
				printf("\n Hashtable");
				Traverse();
					break;
			case 3:
				printf(" Nhap gia tri khoa can them: ");
				scanf("%d", &k);
				insert(k);
				printf("\n Hashtable sau khi them khoa co gia tri %d la: ", k);
				Traverse();
					break;
			case 4:
				printf(" Nhap gia tri khoa can xoa: ");
				scanf("%d", &k);
				Remove(k);
				printf("\n Hashtable: ");
				Traverse();
					break;
			case 5:
				printf(" Nhap gia tri khoa can tim: ");
				scanf("%d", &k);
				p = Search(k);
				if(p)
					printf(" Tim thay khoa co gia tri %d!", k);
				else
					printf(" Khong tim thay khoa co gia tri %d!", k);
				break;
			case 6:
				printf(" Nhap gia tri bucket can xoa: ");
				scanf("%d", &b);
				clearBucket(b);
				printf(" Xoa bucket %d thanh cong!", b);
				printf("\n Hashtable: ");
				Traverse();
					break;
			case 7:
				clear();
				printf(" Xoa Hashtable thanh cong!");
				printf("\n Hashtable: ");
				Traverse();
					break;
			default: printf(" Vui long nhap lai!");
				break;
		}
	}while(chon != 0);
}   
void initBucket(){
	for(int b = 0; b < MAXSIZE; b++)
		bucket[b] = NULL;
}
int HashFunction(int key){
	return key % MAXSIZE;
}
int isEmptyBucket(int b){
	return (bucket[b] == NULL ? TRUE : FALSE);
}
void Push(int b, int x){
	NodePtf p = new HashNode;
	p->key = x;
	p->next = bucket[b];
	bucket[b] = p;
}
void insertAfter(NodePtf p, int k){
	if(p == NULL)
		printf(" Khong them vao Node moi duoc!");
	else{
		NodePtf q = new HashNode;
		q->key = k;
		q->next = p->next;
		p->next = q;
	}
}
void Place(int b, int k){
	NodePtf p, q;
	q = NULL;
	for(p = bucket[b]; p != NULL && k > p->key;  p = p->next){
		q = p;
	}
	if(q == NULL)
		Push(b,k);
	else
		insertAfter(q,k);
}
int isEmpty(){
	for(int b = 0; b < MAXSIZE; b++)
		if(bucket[b] != NULL)
			return FALSE;
	return TRUE;
}
void insert(int k){
	int b = HashFunction(k);
	Place(b,k);
}
void freeNode(NodePtf p){
	delete p;
}
int Pop(int b){
	NodePtf p;
	int k;
	if(isEmptyBucket(b)){
		printf(" Bucket %d bi rong, khong xoa duoc!", b);
		return FALSE;
	}
	p = bucket[b];
	k = p->key;
	bucket[b] = p->next;
	freeNode(p);
	return k;
}
int deleteAfter(NodePtf p){
	NodePtf q;
	int k;
	if( p == NULL|| p->next == NULL){
		printf("\n Xoa khong thanh cong!");
		return FALSE;
	}
	q = p->next;
	k= q->key;
	p->next = q->next;
	freeNode(q);
	return k;
}
void Remove(int k){
	NodePtf q, p;
	int b = HashFunction(k);
	p = bucket[b];
	while(p != NULL && p->key != k){
		q = p;
		p = p->next;
	}
	if(p == NULL)
		printf("\n Khoa %d khong ton tai!\n", k);
	else if(p == bucket[b]){
		Pop(b);
		printf("\n Xoa khoa %d thanh cong!\n", k);
	}
	else{
		deleteAfter(q);
		printf("\n Xoa khoa %d thanh cong!\n", k);
	}
}
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
void clear(){
	for(int b = 0; b < MAXSIZE; b++)
		clearBucket(b);
}
void traverseBucket(int b){
	NodePtf p = bucket[b];
	while(p != NULL){
		printf("[%d] -> ", p->key);
		p = p->next;
		if(!p)
			printf("NULL");
	}
}
void Traverse(){
	for(int b = 0; b <= MAXSIZE; b++){
		printf("\n Bucket thu %d: ", b);
		traverseBucket(b);
	}
}
NodePtf Search(int k){
	int b = HashFunction(k);
	NodePtf p = bucket[b];
	while((k > p->key) && (p != NULL)){
		p = p->next;
	}
	if(p == NULL || k != p->key){
		return NULL;
	}
	else{
		return p;
	}
}
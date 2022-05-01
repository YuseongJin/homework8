#include<stdio.h>
//standard input/output library, 표준 입출력 라이브러리
#include<stdlib.h>
//c표준 유틸리티 함수들을 모아 놓은 헤더파일

/* 필요한 헤더파일 추가 */

typedef struct Node {//구조체 선언
	int key;//int 형 변수 key 멤버 선언
	struct Node* llink;//자기참조 구조체
	struct Node* rlink;//자기참조 구조체ㅠ
} listNode;//구조체 별칭

/* 함수 리스트 */
//원형 선언
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()//메인함수
{
	char command;//char형 변수 선언, 명령어
	int key;//int형 변수 선언, 키보드
	listNode* headnode=NULL;//headnode의 값을 NULL로 초기화

	printf("[----- [Yuseong Jin] [2018038022] -----]");//이름, 학번 출력

	do{//do-while문을 통하여 반복 출력
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		//메뉴 출력

		printf("Command = ");
		scanf(" %c", &command);
		//명령어 입력받기

		switch(command) {//스위치문
		case 'z': case 'Z'://z키를 입력 받았을 때
			initialize(&headnode);//initialize함수 실행
			break;//스위치문 끝
		case 'p': case 'P'://p키를 입력 받았을 때
			printList(headnode);//printList함수 실행
			break;//스위치문 끝
		case 'i': case 'I'://i키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertNode(headnode, key);//insertNode함수 실행
			break;//스위치문 끝
		case 'd': case 'D'://d키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			deleteNode(headnode, key);//deleteNode 함수 실행
			break;//스위치문 끝
		case 'n': case 'N'://n키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertLast(headnode, key);//insertLast 함수 실행
			break;//스위치문 끝
		case 'e': case 'E'://e키를 입력 받았을 때
			deleteLast(headnode);//deleteLast 함수 실행
			break;//스위치문 끝
		case 'f': case 'F'://f키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertFirst(headnode, key);//insertFirst 함수 실행
			break;//스위치문 끝
		case 't': case 'T'://t키를 입력 받았을 때
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;//스위치문 끝
		case 'r': case 'R'://r키를 입력 받았을 때
			invertList(headnode);//invertList 함수 실행
			break;//스위치문 끝
		case 'q': case 'Q'://q키를 입력 받았을 때
			freeList(headnode);//freeList 함수 실행
			break;//스위치문 끝
		default://이 외의 입력을 받았을 때 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			//경고문 출력
			break;//스위치문 끝
		}

	}while(command != 'q' && command != 'Q');
	//q키를 사용하기 전까지 계속 반복

	return 1;//종료
}


int initialize(listNode** h) {//초기화 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;//종료
}

int freeList(listNode* h){//리스트 할당해제 함수

	if(h->rlink == h)//h의 rlink의 값이 h와 같다면
	{
		free(h);//h할당해제
		return 1;//종료
	}

	listNode* p = h->rlink;
	//listnode 포인트 변수 p 선언 후 h의 rlink 값 대입

	listNode* prev = NULL;
	//listnode 포인트 변수 prev 선언 후 NULL로 초기화
	while(p != NULL && p != h) {//p가 NULL값이 아니고, p가 h와 다르다면
		prev = p;//prev를 p로 초기화
		p = p->rlink;//p에 p의 rlink값 대입
		free(prev);//prev 할당해제
	}
	free(h);//h 할당해제
	return 0;//종료
}



void printList(listNode* h) {//list출력 함수
	int i = 0;//int형 변수 i선언 후 0으로 초기화
	listNode* p;//listnode 포인트 변수 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//headnode가 NULL이라면
		printf("Nothing to print....\n");
		//출력할 내용이 없음을 출력
		return;//종료
	}

	p = h->rlink;//p에 h의 rlink값 대입

	while(p != NULL && p != h) {//p가 NULL이 아니고 h와 다르다면
		printf("[ [%d]=%d ] ", i, p->key);
		//i, 입력한 키 값 출력
		p = p->rlink;//다음 노드를 가르킴
		i++;//i값 증감
	}
	printf("  items = %d\n", i);//입력한 노드 수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//헤드노드의 llink, head, rlink 출력

	i = 0;//i를 0으로 초기화
	p = h->rlink;//h의 rlink의 값을 p에 대입
	while(p != NULL && p != h) {//p가 NULL이 아니고 h와 다르다면
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		//i, 입력한 키 값, p의 llink, node, rlink 출력
		p = p->rlink;//다음 노드를 가르킴
		i++;//i값 증감
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {//마지막 삽입 함수

	if (h == NULL) return -1;//h가 NULL이면 비정상 종료

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listnode 포인터 변수 node 선언후 동적 메모리 할당 
	node->key = key;
	//node의 key 값에 key값 대입
	node->rlink = NULL;
	node->llink = NULL;
	//rlink와 llink를 순서대로 NULL로 초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */
	//h의 rlink의 값이 h와 같다면
	{
		h->rlink = node;//node의 값을 헤드의 rlink에 대입
		h->llink = node;//node의 값을 헤드이 llink에 대입
		node->rlink = h;//h의 값을 노드의 rlink에 대입
		node->llink = h;//h의 값을 노드의 llink에 대입
	} else {//이 외
		h->llink->rlink = node;//node의 값을 h의 연결드리스트에 대입
		node->llink = h->llink;//h의 link값을 node의 llink에 대입
		h->llink = node;//node를 h의 llink에 대입
		node->rlink = h;//h를 node의 rlink에 대입
	}

	return 1;//종료
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {////마지막삭제 함수

	if (h->llink == h || h == NULL)//h의 llink값이 h와 같거나 NULL 이라면
	{
		printf("nothing to delete.\n");
		//삭제할 내용이 없음을 출력
		return 1;//종료
	}

	listNode* nodetoremove = h->llink;
	//리스트노드 포인트변수 nodetoremove 선언 후 h의 llink값 대입

	/* link 정리 */
	nodetoremove->llink->rlink = h;
	//h를 nodetoremove 연결드리스트에 대입
	h->llink = nodetoremove->llink;
	//nodetoremove의 llink값을 h의 llink에 대입

	free(nodetoremove);//nodetoremove할당해제

	return 1;//종료
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
//list 처음에 key에 대한 노드하나를 추가함수

	listNode* node = (listNode*)malloc(sizeof(listNode));
	////listnode 포인터 변수 node 선언후 동적 메모리 할당 
	node->key = key;
	//node의 key 값에 key값 대입
	node->rlink = NULL;
	node->llink = NULL;
	//node의 r,llink 값을 NULL로 초기화


	node->rlink = h->rlink;
	//node의 rlink에 h의 rlink값 대입
	h->rlink->llink = node;
	//node의 값을 h의 연결드리스트에 대입
	node->llink = h;
	//h의 값을 node의 llink에 대입
	h->rlink = node;
	//node의 값을 h의 rlink에 대입


	return 1;//종료
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
//list의 첫번째 노드 삭제 함수	

	if (h == NULL || h->rlink == h)
	//h가 NULL이거나 h의 rlink값이 h와 같다면
	{
		printf("nothing to delete.\n");
		//삭제할 것이 없음을 출력
		return 0;
		//종료
	}

	listNode* nodetoremove = h->rlink;
	//리스트노드 포인트변수 nodetoremove 선언 후 h의 rlink값 대입

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);
	//nodetoremove 할당해제

	return 1;
	//종료

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {//리스트 역순배치 함수


	if(h->rlink == h || h == NULL) {
	//h가 NULL이거나 h의 rlink값이 h와 같다면
		printf("nothing to invert...\n");
		//삭제할 것이 없음을 출력
		return 0;
		//종료
	}
	listNode *n = h->rlink;
	//listnode 포인트변수 n선언 후 h의 rlink값 대입
	listNode *trail = h;
	//listnode 포인트변수 trail선언 후 h값 대입
	listNode *middle = h;
	//listnode 포인트변수 middle선언 후 h값 대입

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){
	//n이 NULL가 다르고 h와도 다르다면
		trail = middle;//trail에 middle값 대입
		middle = n;//middle에 n값 대입
		n = n->rlink;//n에 n의 rlink값대입
		middle->rlink = trail;//middle의 rlink에 trail값 대입
		middle->llink = n;//middle의 llink에 n값 대입
	}

	h->rlink = middle;//h의 rlink에 middle값 대입

	return 0;//종료
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {//노드 삽입 함수

	if(h == NULL) return -1;
	//h가 NULL이라면 비정상 종료

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listnode 포인터 변수 node 선언후 동적메모리 할당
	node->key = key;
	//key값을 node의 key에 대입
	node->llink = node->rlink = NULL;
	//노드의 r,l link 값을 순서대로 NULL로 초기화

	if (h->rlink == h)//h의 rlink가 h와 같다면
	{
		insertFirst(h, key);//insertFirst함수 실행
		return 1;//종료
	}

	listNode* n = h->rlink;
	//리스트노드 포인트변수 n 선언 후 h의 rlink 값 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
	//n이 NULL값과 다르고, n이 h와 다르다면
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
				//insertFirst함수 실행
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
				
			}
			return 0;//종료
		}

		n = n->rlink;//n에 rlink값 대입
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	//insertlast함수 실행
	return 0;//종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
//노드삭제 함수
	if (h->rlink == h || h == NULL)
	//rlink값이 h와 같거나, h가 NULL 값이라면
	{
		printf("nothing to delete.\n");
		//삭제할 것이 없음을 출력
		return 0;//종료
	}

	listNode* n = h->rlink;
	//리스트노드 포인트변수 n 선언 후 rlink 값 대입

	while(n != NULL && n != h) {
		//n이 null값과 다르고 n이 h값과 다르다면
		if(n->key == key) {//key값 비교
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);//deleteFirst 함수 실행
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);//deleteLast 함수 실행
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				
				free(n);//n 할당해제
			}
			return 0;//종료
		}

		n = n->rlink;//n에 rlink값 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	//키에 대한 노드를 찾을 수 없음을 출력
	return 0;//종료
}



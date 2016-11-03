#include <stdlib.h>
#include <string.h>
#include "pcc.h"

/*************** 动态数组相关函数 ***************/

/*动态数组初始化*/
Vector InitVector(int VectorSize) {
	Vector Vec;
	if (VectorSize < MinVectorSize) {
		Error("Vector size too small!");
	}
	Vec = malloc(sizeof(struct DynamicVector));
	if (Vec == NULL) {
		FatalError("Out of space!!");
	}
	Vec->Capacity = VectorSize;
	Vec->Data = malloc(sizeof(struct TokenWord) * Vec->Capacity);
	if (Vec->Data == NULL) {
		FatalError("Out of space!!");
	}
	Vec->Size = 0;
	return Vec;
}
/*动态数组重置Capacity*/
void VectorRealloc(Vector Vec) {
	Token *P;
	P = realloc(Vec->Data, Vec->Capacity * 2);
	if (P == NULL) {
		FatalError("Out of space!!");
	}
	Vec->Capacity *= 2;
}
/*动态数组添加元素*/
Token VectorAdd(Vector Vec, HashTable H, String Str) {
	Token Tk;
	if (Vec->Size + 1 > Vec->Capacity) {
		VectorRealloc(Vec);
	}
	if (!Find(Str, H)) { //如果Tk不在哈希表中
		Tk = malloc(sizeof(struct TokenWord));
		if (Tk = NULL) {
			Error("Out of space!");
		}
		Tk->String = malloc(sizeof(char) * Str->Size + 1);
		if (Tk->String == NULL) {
			Error("Out of space!");
		}
		strcpy(Tk->String, Str->Data);
		Tk->Next = H->TheTokens[Hash(Str->Data, H)];
		H->TheTokens[Hash(Str, H)] = Tk;

		Vec->Data[Vec->Size++] = Tk;
	}
	return Tk;
}
/*释放动态数组*/
void VectorFree(Vector Vec) {
	int i;
	for (i = 0; i < Vec->Size; ++i) {
		free(Vec->Data[i]);
	}
	free(Vec->Data);
	Vec->Data = NULL;
}


/*************** 动态字符串相关函数 ***************/

/*字符串初始化*/
String InitString(int StringSize) {
	String Str;
	if (StringSize < MinStringSize) {
		Error("String size too small!");
	}
	Str = malloc(sizeof(struct DynamicString));
	if (Str == NULL) {
		FatalError("Out of space!");
	}
	Str->Data = malloc(sizeof(char) * StringSize);
	if (Str->Data == NULL) {
		FatalError("Out of space!");
	}
	Str->Capacity = StringSize;
	Str->Size = 0;
}
/*重置字符串容量*/
void StringRealloc(String Str) {
	char *P;
	P = realloc(Str->Data, Str->Capacity * 2);
	if (P == NULL) {
		FatalError("Out of space!");
	}
	Str->Capacity *= 2;
}
/*向字符串添加字符*/
void StringAdd(String Str, char c) {
	if (Str->Size + 1 > Str->Capacity) {
		StringRealloc(Str);
	}
	Str->Data[Str->Size] = c;
	Str->Data[++Str->Size] = '\0';
}
/*重置字符串*/
void StringReset(String Str) {
	Str->Size = 0;
}


/*************** 哈希表相关函数 ***************/

/*哈希函数定义*/
int Hash(char *Key, HashTable H) {
	int HashVal = 0;
	while (*Key != '\0') {
		HashVal = (HashVal << 5) + *Key++;
	}
	return HashVal % H->TableSize;
}
/*哈希表初始化*/
HashTable InitHash(int TableSize) {
	HashTable H;
	int i;
	if (TableSize < MinTableSize) {
		Error("Table size too small!");
		return NULL;
	}
	H = malloc(sizeof(struct HashTbl));
	if (H == NULL) {
		FatalError("Out of space!");
	}
	H->TableSize = TableSize;
	H->TheTokens = malloc(sizeof(Token) * H->TableSize);
	if (H->TheTokens == NULL) {
		FatalError("Out of Space!");
	}
	for (i = 0; i < H->TableSize; ++i) {
		H->TheTokens[i] = NULL;
	}
	return H;
}
/*哈希表查找*/
Position Find(String Str, HashTable H) {
	Position Pos;
	Pos = H->TheTokens[Hash(Str->Data, H)];
	while (Pos != NULL && Pos->String != Str) {
		Pos = Pos->Next;
	}
	return Pos;
}
/*哈希表插入*/
void Insert(Token Tk, HashTable H) {
	Position Pos;
	Pos = Find(Tk, H);
	if (Pos == NULL) {
		Tk->Next = H->TheTokens[Hash(Tk->String, H)];
		H->TheTokens[Hash(Tk->String, H)] = Tk;
	}
}


typedef char STDataType;

typedef struct Stack {
	STDataType* _a;
	int _top;// 栈顶
	int _capacity; // 容量
}Stack;

// 初始化栈 
void StackInit(Stack* ps)
{
	ps->_a = NULL;
	ps->_top = 0;
	ps->_capacity = 0;
}

//检查容量
void CheckCapacity(Stack* ps)
{
	if (ps->_top == ps->_capacity)
	{
		size_t newCapacity = ps->_capacity == 0 ? 4 : ps->_capacity * 2;
		ps->_a = (STDataType*)realloc(ps->_a, newCapacity * sizeof(STDataType));
		if (ps->_a)
			ps->_capacity = newCapacity;
	}
}

// 入栈
void StackPush(Stack* ps, STDataType data)
{
	CheckCapacity(ps);
	ps->_a[ps->_top++] = data;

}

// 出栈 
void StackPop(Stack* ps)
{
	assert(ps && ps->_top > 0);
	--ps->_top;
}

// 获取栈顶元素
STDataType StackTop(Stack* ps)
{
	assert(ps);
	return ps->_a[ps->_top - 1];
}


// 检测栈是否为空，如果为空返回非零结果，如果不为空返回0
int StackEmpty(Stack* ps)
{
	assert(ps);
	return ps->_top == 0 ? 1 : 0;
}

// 销毁栈 
void StackDestroy(Stack* ps)
{
	assert(ps);
	free(ps->_a);
	ps->_a = NULL;
	ps->_capacity = ps->_top = 0;
}


bool isValid(char * s)
{
    Stack st;
    StackInit(&st);
    char* symbols[] = {"[]","{}","()"};

    while(*s)
    {
        if(*s == '{' || *s == '(' || *s == '[')
        {
            StackPush(&st, *s);
        }
        else 
        {
            if(StackEmpty(&st))
                return false;
                char top = StackTop(&st);
                StackPop(&st);
            for(int i = 0; i < 3; ++i)
            {
                if(*s == symbols[i][1] && top != symbols[i][0])er
                    return false;
            }
        }
        ++s;
    }
    bool ret = StackEmpty(&st);
    StackDestroy(&st);
    return ret;
}
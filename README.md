###Доступные проверки:
1) Одинаковые условия
```
if (a==0 || a==0)
```
2) Одинаковые ветки if-else
```
if (a==0) 
{foo();} 
else 
{foo();}
```
3) Выражение соответсвует предыдущему
```
if (a==0)
{...}
else if (a==0)
{...}
```
4) Перепутаны 2й и 3й аргументы memset
```memset(buf,sizeof(buf),0)```
5) не верный размер для заполнения памяти int или short
```
int arr[10];
memset(arr, 0, 10);
// так как memset и memcpy принимают размер в байтах, необходимо домножить на sizeof(int)
```
6) при выделении памяти для строки не учитывается \0 символ
```
malloc(strlen(str)); // -> malloc(strlen(str) + 1)
new char[strlen(str)]; // -> new[strlen(str) + 1]
```
7) выражение внутри strlen
`strlen(str + 1);`

8) лучше переписать if (strcmp(...)) на if (strcmp(...) != 0), тоже для strncmp

9) одинаковые аргументы strcmp, memmove, memcpy, strstr, strncmp

10) выражение внутри sizeof
```
sizeof(A++);
sizeof(buf-1);
sizeof(buf*num);
```
11) перемножение sizeof на sizeof

12) выделение памяти для одного простого типа с инициализацией
```
new int(n)
new char(n)
```

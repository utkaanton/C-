#include <iostream>//библиотека ввода/вывода
#include <math.h>//библиотека для работы с мат. ф.
#include <cstdlib>//библиотека для работы со случайными числами
#include <string>//библиотека для работы со строками
#include <fstream>//библиотека для работы с файлами
#include <iomanip>//библиотека для отступов

using namespace std;//пространство имен std

template <typename T>//переменный тип 
class Matrix{//класс матриц
public:
    int size;//размер матрицы
    T **dinamic_array;//динамический масив
    Matrix (int size){//инициализация массива
        this->size=size;
        dinamic_array = new T* [size];//динамический массив
        for (int i = 0; i < size; i++) {//заполнение динамического массива
            dinamic_array[i] = new T [size];  
        }
        
        if(typeid(T)==typeid(3)){//проверка на получаемый тип данных
            for(int i = 0; i<size;i++){//заполнение массива случайными числами
                for(int j=0; j<size; j++){
                    dinamic_array[i][j]=rand()%10;
                }
            }
        }
        else{
            for(int i = 0; i<size;i++){//заполнение массива
                for(int j=0; j<size; j++){
                    dinamic_array[i][j]=(rand()%9)*0.1+0.1;
                }
            }
        }   
    }
    
    T* &operator[](int i){//перегрузка оператора индексации
        return dinamic_array[i];
    };

    void GetMatrix(){//вывод матрицы
        for(int i = 0; i<size;i++){//перебор двумерного массива 
            for(int j=0; j<size; j++){
                cout << dinamic_array[i][j];
                cout << " ";
            }
            cout << endl;
        }
    }
    void FromFile(string str){//получение данных из файла
        int count=0;//счетчик
        string buf="";//буфер
        for(int i = 0; i<size;i++){//заполненение двумерного массива
            for(int j=0; j<size; j++){
                buf=str[count];
                dinamic_array[i][j]=stoi(buf);
                count++;
            }
        }
    }
    
    int FindElm(T num){//найти элемент
        int sum=0;//сумма
        for(int i = 0; i<size;i++){//перебор двумерного массива
            for(int j=0; j<size; j++){
                if(dinamic_array[i][j]==num)sum++;
            }
        }
        return sum;//количество найденных элементов
    }
}; 

void ReadingFile();//чтение истории
float Datr(string jop);//строка в дробь
string DataFromFile();//данные из фалйа
template<typename T>//переменный тип
void WriteToFile(Matrix<T> x, bool enter);//запись матрицы в файл
template<typename T>//переменный тип 
void WriteMatrix(Matrix<T> x);//запись матрицы в файл
template<typename T>//переменный тип 
void WriteRes(T num, int sum);//запись истории
void DeleteLog();
int main()
{
    setlocale(LC_ALL, "RUSSIAN");//добавления русского языка
    srand(time(NULL));//ф. для случайных чисел
    string choice=" ";//переменная выбора
    int size;//размер
    string number;//число
    cout << "Программа-счетчик. Выдает количество вхождений введенного числа в массив случайных чисел" << endl;
    cout << "Выполнил Осетров А.А. гр.ОБ-10.03.01-11" << endl << endl;
    
    
    for(;;){//зацикливание
        cout << endl <<"Меню:" << endl << "| 1 | Генерация квадратной матрицы случайных ЦЕЛЫХ чисел в диапазоне от 0 до 10" << endl <<"| 2 | Генерация квадратной матрицы случайных ДРОБНЫХ чисел кратных 0.1 в диапазоне от 0.1 до 0.9"<<endl<<"| 3 | Получить матрицу из файла data_intut.txt(в папке программы)"<<endl<<"| 4 | Просмотр истории"<< endl<<"| 5 | Очистить историю"<< endl <<"|   | Выйти - введите любую клавишу"<< endl << "Ввод --->";
        cin >> choice;
        if (choice=="1"){
            cout << "Задайте размер матрицы (от 2 до 10) -->";
            cin >> size;
            Matrix<int> A(size);
            WriteToFile(A,0);
            A.GetMatrix();
            cout << endl;
            for(;;){//зацикливание
                cout << "Найти количество входов значения в массив"<<endl;
                cout << "Введите значение для поиска(выход - введите ""g"") -->";
                cin >> number;
                if (number=="g" || number=="G")break;//выход
                else cout <<"Количество вхождений в массив = " <<A.FindElm(stoi(number))<<endl<<endl;
                WriteRes(stoi(number),A.FindElm(stoi(number)));
            }
        }
        else if(choice=="2"){
            cout << "Задайте размер матрицы (от 2 до 10) -->";
            cin >> size;
            Matrix<float> A(size);
            WriteToFile(A,0);
            A.GetMatrix();
            cout << endl;
            for(;;){//зацикливание
                float test;
                cout << "Найти количество входов значения в массив"<<endl;
                cout << "Введите значение для поиска, в формате 0.0 (выход - введите ""g"") -->";
                cin >> number;
                size = A.FindElm(Datr(number));
                if (number=="g" || number=="G")break;//выход
                else cout <<"Количество вхождений в массив = " <<A.FindElm(Datr(number))<<endl<<endl;
                WriteRes(Datr(number),size);
            }
        }
        else if(choice=="3"){
            Matrix<int> A(3);
            A.FromFile(DataFromFile());
            WriteToFile(A,1);
            cout << endl;
            A.GetMatrix();
            cout << endl;
            for(;;){//зацикливание
                cout << "Найти количество входов значения в массив"<<endl;
                cout << "Введите значение для поиска(выход - введите ""g"") -->";
                cin >> number;
                if (number=="g" || number=="G")break;//выход
                else cout <<"Количество вхождений в массив = " <<A.FindElm(stoi(number))<<endl<<endl;
                WriteRes(stoi(number),A.FindElm(stoi(number)));
            }
        }
        else if(choice=="4"){
            ReadingFile();
        }
        else if(choice=="5"){
            DeleteLog();
        }
        else break;
    }

}

template<typename T>
void WriteToFile(Matrix<T> x, bool enter){
    ofstream file;//объект для записи в файл
	file.open("output_data.txt", ios_base::app);//открытие файла для дополнительной записи  
    file << endl <<"============================================================"<<endl;  
    if(enter == 1)file<<"Матрица введена из файла data_input.txt (в папке программы)"<<endl;
    else file << "Матрица сгенерирована с заданным размером "<< endl;
    file.close();//закрытие файла
    WriteMatrix(x);
}
template<typename T>
void WriteMatrix(Matrix<T> x){
    ofstream file;//объект для записи в файл
	file.open("output_data.txt", ios_base::app);//открытие файла для дополнительной записи 
    for(int i=0;i<x.size;i++){//двумерный массив в файл
        for(int j=0;j<x.size;j++){
            file << x.dinamic_array[i][j] << " ";
        }
        file << endl;
    }
    file << endl;
    file.close();//закрытие файла 
}
template<typename T>
void WriteRes(T num, int sum){
    ofstream file;//объект для записи в файл
	file.open("output_data.txt", ios_base::app);//открытие файла для дополнительной записи
    file << "Значение - " << num << "  встретилось - " << sum << endl;
    file.close();//закрытие файла
}

string DataFromFile(){
    ifstream file;//объект для чтения файла
	file.open("input_data.txt");//путь к файлу
    string buf;//буфер
    string number;//буфер
    while (!file.eof())//проверка на конец файла
	{
		getline(file, buf);//запись в строки файла в буфер
		break;
	}
    file.close();//закрытие файла
    return buf;
}

float Datr(string jop){
    string buf=" ";
    buf=jop[2];
    if (jop[0]!='0')return 1.0;
    else return stoi(buf)*0.1;
}

void ReadingFile(){
	ifstream file;//объект для чтения файла
	file.open("output_data.txt");//путь к файлу
	string line = " ";//буфер для строки
	while (!file.eof())//проверка на конец файла
	{
		getline(file, line);//запись в строки файла в буфер
		cout << line << endl;//вывод содержимого буфера
	}
	file.close();//закрытие файла
}

void DeleteLog(){
	ofstream file;//объект для записи в файл
	file.open("output_data.txt");//открытие файла
	file << endl <<"================================================================================="<<endl<<"Файл data_output.txt находится в папке программы" << endl <<"================================================================================="<<endl;//запись
	file.close();//закрытие файла
}
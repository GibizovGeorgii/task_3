Данный алгоритм находит собственные значения матрицы А:   
Матрица A приводится к почти диагональному виду методом вращений, затем преобразуется к диагональной с помощью LR алгоритма.

Чтобы собрать проект, достаточно прописать:   
make -f MakeFile    

Будет собран исполняемый файл gogo  

Файл gogo запускается следующей командой:    
./gogo n q m k  
где n - размер матрицы, m - параметр вывода (выводится подматрица m x m), q - точность вычислений (например 10e-15),   
k - способ задания матрицы:  
значения от 1 до 4 - различные автоматически заполняемые матрицы  
значение 5 - требуется добавить после команды текстовый файл, содержащий вашу матрицу:    
./gogo n m 4 t input.txt

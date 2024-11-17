# Matrix
# Установка
Склонируйте репозиторий, перейдите в папку с ним.
Сборка проекта:
```sh
mkdir build
cd build/
```
Вы создали папку, в которой будет собираться проект и перешли в неё
```sh
cmake ..
make
```
Чтобы запустить мои unit tests, вам понадобится установить Google Tests.

# Описание работы
Моя матрица умеет работать ТОЛЬКО с квадратными матрицами. Для входных зачений вы должны указать следующее :
первый аргумент  - это размер квадратной матрицы ( либо кол-во столбцов, либо кол-во строк ), все остальные аргументы - её члены.

# Как с этим работать 
## Тесты :
Все тесты лежат в папке с репозиторием в папке "tests". 
Мои e2e tests работают для определителей матриц. 
Чтобы запустить тесты, в папке build напишите "ctest"
## Свои данные
Чтобы протестировать свои данные, напишите 
```sh
./matrix *
```
где вместо * укажите либо "< my_file_name.txt", либо ничего не указывайте и нажмите Enter, после чего вводите свои данные в формате моих тестов.

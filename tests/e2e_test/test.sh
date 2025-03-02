#!/bin/bash

data_dir="data"
files=("$data_dir"/*.in)
epsilon=0.0001  # Порог сравнения

if [ ${#files[@]} -eq 0 ]; then
    echo "Нет файлов с расширением .in в папке $data_dir."
    exit 1
fi

for file in "${files[@]}"; do 
    base_name="${file%.in}"  # Убираем расширение .in
    expected_file="${base_name}.out"

    echo "Обработка файла: $file"

    if [ ! -f "$expected_file" ]; then
        echo "Файл с ожидаемым результатом ($expected_file) не найден!"
        continue
    fi

    echo "Определитель матрицы:"
    result=$(../../build/matrix < "$file")  # Запускаем программу и сохраняем результат
    expected=$(cat "$expected_file")  # Читаем ожидаемый результат

    echo "Результат: $result"
    echo "Ожидалось: $expected"

    difference=$(awk -v r="$result" -v e="$expected" 'BEGIN { print (r - e) < 0 ? -(r - e) : (r - e) }')

    if (( $(echo "$difference < $epsilon" | bc -l) )); then
        echo "✅ Тест пройден!"
    else
        echo "❌ Ошибка! Разница $difference превышает порог $epsilon."
    fi
    echo "-----------------------------------"
done

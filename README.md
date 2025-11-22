<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=6,11,20&height=200&section=header&text=%F0%9F%9A%97%20Car%20Dealership%20Management%20System&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=32"/>

<div style="background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); padding: 25px; border-radius: 20px; margin: 25px 0; box-shadow: 0 15px 35px rgba(0,0,0,0.3);">

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-6.9-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-orange?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge)

**<span style="color: white; font-size: 18px;">Современная система управления автосалоном с графическим интерфейсом</span>**

<div style="margin-top: 15px;">

[Возможности](#-возможности) • [Установка](#-установка) • [Использование](#-использование) • [Структура проекта](#-структура-проекта) • [Технологии](#-технологии)

</div>

</div>

</div>

<div align="center">

<img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=28&duration=2000&pause=1000&color=667eea&center=true&vCenter=true&width=600&lines=%F0%9F%93%8B+%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5+%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B0" alt="Описание проекта" />

</div>

<div style="background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%); padding: 20px; border-radius: 15px; margin: 20px 0; box-shadow: 0 8px 16px rgba(0,0,0,0.1); border-left: 5px solid #667eea;">

**Car Dealership Management System** — это настольное приложение для управления автосалоном, разработанное на C++17 с использованием Qt6 Widgets. Система предоставляет удобный графический интерфейс для ведения каталога автомобилей, управления клиентской базой, оформления продаж с автоматическим расчётом скидок и генерации аналитических отчётов.

</div>

### 🎯 Основные цели проекта

<div style="background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); padding: 15px; border-radius: 10px; margin: 15px 0;">

- ✨ **Автоматизация процессов** управления автосалоном
- 📦 **Упрощение работы** с каталогом автомобилей и клиентской базой
- 💰 **Автоматический расчёт скидок** на основе истории покупок и сезонных факторов
- 📊 **Генерация детальных отчётов** о продажах
- 🚀 **Простое развёртывание** без необходимости в серверной инфраструктуре

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%E2%9C%A8%20%D0%92%D0%BE%D0%B7%D0%BC%D0%BE%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D0%B8&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden;">

<div style="color: white;">

### 🚙 Управление автомобилями
- **Каталог автомобилей** — отображение в виде карточек с изображениями и характеристиками
- **Добавление/редактирование** — ввод полной информации об автомобиле (бренд, модель, год, цена, цвет, мощность, трансмиссия, VIN)
- **Дополнительные опции** — настройка опций автомобиля с автоматическим пересчётом цены
- **Управление остатками** — отслеживание количества автомобилей на складе
- **Резервирование** — возможность резервирования автомобилей для клиентов

### 👥 Управление клиентами
- **Клиентская база** — ведение списка клиентов с контактной информацией
- **Баланс счёта** — отслеживание баланса каждого клиента
- **История покупок** — автоматическое отслеживание истории покупок для расчёта скидок

### 💰 Оформление продаж
- **Автоматический расчёт скидок:**
  - 🎁 **10%** для новых клиентов (первая покупка)
  - 🏆 **5%** для постоянных клиентов (более одной покупки)
  - ❄️ **7%** сезонная скидка (зимние месяцы)
- **Выбор опций** — настройка дополнительных опций при оформлении продажи
- **Проверка баланса** — автоматическая проверка достаточности средств у клиента
- **Управление остатками** — автоматическое уменьшение остатков на складе

### 🔍 Поиск и фильтрация
- **Многофункциональный поиск** по различным критериям:
  - По бренду
  - По модели
  - По диапазону цен
  - По цвету
  - По диапазону мощности
  - По типу трансмиссии
- **Горячая клавиша** `Ctrl+F` для быстрого доступа к поиску

### 📊 Отчёты и аналитика
- **Отчёты о продажах** — генерация отчётов за выбранный период
- **Статистика** — общее количество продаж и выручка
- **Экспорт данных:**
  - 📄 HTML/CSV для Excel
  - 📝 RTF для Word
- **Группировка по датам** — удобное представление данных

### 💾 Хранение данных
- **Файловое хранилище** — данные сохраняются в текстовых файлах:
  - `cars.txt` — каталог автомобилей
  - `clients.txt` — клиентская база
  - `sales.txt` — история продаж
- **Автоматическое сохранение** при закрытии приложения
- **Человекочитаемый формат** — возможность ручного редактирования при необходимости

</div>

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%F0%9F%9B%A0%EF%B8%8F%20%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden;">

<div style="color: white;">

### Требования

- **C++17** или выше
- **Qt 6.9** или выше (модуль Widgets)
- **CMake** или **qmake** для сборки
- **Компилятор:**
  - Windows: MinGW 64-bit или MSVC
  - Linux: GCC 7+ или Clang 8+
  - macOS: Clang 10+

### Сборка проекта

#### Использование qmake (рекомендуется)

```bash
# Клонирование репозитория
git clone <repository-url>
cd Coursework

# Генерация Makefile
qmake coursework.pro

# Сборка проекта
make          # Linux/macOS
mingw32-make  # Windows (MinGW)
nmake         # Windows (MSVC)
```

#### Использование CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Запуск

После успешной сборки исполняемый файл будет находиться в папке `build/`:

```bash
# Linux/macOS
./coursework

# Windows
coursework.exe
```

</div>

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%F0%9F%8E%AE%20%D0%98%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden;">

<div style="color: white;">

### Основной интерфейс

Приложение состоит из трёх основных вкладок:

1. **🚗 Cars** — каталог автомобилей
   - Просмотр автомобилей в виде карточек
   - Добавление новых автомобилей
   - Редактирование и удаление
   - Резервирование и продажа

2. **👨🏻‍💼 Clients** — управление клиентами
   - Просмотр списка клиентов
   - Добавление новых клиентов
   - Удаление клиентов
   - Отслеживание баланса

3. **🏷️ Sales** — история продаж
   - Просмотр всех продаж
   - Детальная информация о каждой продаже
   - Генерация отчётов

### ⌨️ Горячие клавиши

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; margin: 10px 0; border-left: 3px solid rgba(255,255,255,0.5);">

- <kbd style="background: rgba(255,255,255,0.3); color: white; padding: 5px 10px; border-radius: 5px; border: 1px solid rgba(255,255,255,0.4);">Ctrl</kbd> + <kbd style="background: rgba(255,255,255,0.3); color: white; padding: 5px 10px; border-radius: 5px; border: 1px solid rgba(255,255,255,0.4);">F</kbd> — открыть диалог поиска автомобилей

</div>

### 📋 Основные операции

#### 🚗 Добавление автомобиля

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; margin: 10px 0; border-left: 3px solid rgba(255,255,255,0.5);">

1. Перейдите на вкладку **Cars**
2. Нажмите кнопку **"+ Add Car"**
3. Заполните форму:
   - Выберите бренд и модель
   - Укажите год выпуска, цену, цвет
   - Введите мощность и тип трансмиссии
   - Укажите остаток на складе и VIN-код
   - Выберите дополнительные опции (опционально)
4. Нажмите **OK**

</div>

#### 💰 Оформление продажи

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; margin: 10px 0; border-left: 3px solid rgba(255,255,255,0.5);">

1. Нажмите кнопку **"Sell"** на карточке автомобиля или используйте меню
2. Выберите автомобиль и клиента
3. Настройте дополнительные опции (если необходимо)
4. Система автоматически рассчитает:
   - Исходную цену
   - Размер скидки
   - Итоговую цену
5. Подтвердите продажу

</div>

#### 🔍 Поиск автомобилей

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; margin: 10px 0; border-left: 3px solid rgba(255,255,255,0.5);">

1. Нажмите <kbd style="background: rgba(255,255,255,0.3); color: white; padding: 5px 10px; border-radius: 5px; border: 1px solid rgba(255,255,255,0.4);">Ctrl</kbd> + <kbd style="background: rgba(255,255,255,0.3); color: white; padding: 5px 10px; border-radius: 5px; border: 1px solid rgba(255,255,255,0.4);">F</kbd> или используйте меню поиска
2. Выберите тип поиска (бренд, модель, цена и т.д.)
3. Введите критерии поиска
4. Нажмите **"Search"**
5. Результаты отобразятся в виде карточек

</div>

#### 📊 Генерация отчёта

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; margin: 10px 0; border-left: 3px solid rgba(255,255,255,0.5);">

1. Перейдите на вкладку **Sales**
2. Нажмите **"📊 Sales Report"**
3. Выберите период (начальная и конечная дата)
4. Нажмите **"Generate Report"**
5. При необходимости экспортируйте в Excel или Word

</div>

</div>

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%F0%9F%93%81%20%D0%A1%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D0%B0%20%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B0&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden;">

<div style="color: white;">

```
Coursework/
├── includes/              # Заголовочные файлы
│   ├── car.h             # Модель автомобиля
│   ├── client.h          # Модель клиента
│   ├── sale.h            # Модель продажи
│   ├── dealership_manager.h  # Менеджер автосалона
│   ├── mainwindow.h      # Главное окно
│   ├── car_repository.h  # Репозиторий автомобилей
│   ├── client_repository.h   # Репозиторий клиентов
│   ├── sale_repository.h     # Репозиторий продаж
│   ├── sale_service.h    # Сервис расчёта скидок
│   └── ...
├── src/                  # Исходные файлы
│   ├── main.cpp          # Точка входа
│   ├── mainwindow.cpp    # Реализация главного окна
│   ├── car.cpp           # Реализация модели автомобиля
│   ├── dealership_manager.cpp
│   └── ...
├── images/               # Изображения автомобилей
├── icons/                # Иконки приложения
├── coursework.pro        # Файл проекта qmake
└── README.md            # Документация
```

### 🏗️ Архитектура

Проект следует принципам **разделения ответственности**:

<div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 15px; margin: 20px 0;">

<div style="background: white; padding: 15px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); border-top: 4px solid #667eea;">

**🎨 UI Layer**  
`MainWindow`, диалоги  
Графический интерфейс и взаимодействие с пользователем

</div>

<div style="background: white; padding: 15px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); border-top: 4px solid #764ba2;">

**⚙️ Business Logic**  
`DealershipManager`, сервисы  
Бизнес-логика и координация операций

</div>

<div style="background: white; padding: 15px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); border-top: 4px solid #f093fb;">

**💾 Data Layer**  
Репозитории  
Работа с файловым хранилищем

</div>

<div style="background: white; padding: 15px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); border-top: 4px solid #4facfe;">

**📦 Models**  
`Car`, `Client`, `Sale`  
Модели данных

</div>

</div>

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%F0%9F%94%A7%20%D0%A2%D0%B5%D1%85%D0%BD%D0%BE%D0%BB%D0%BE%D0%B3%D0%B8%D0%B8&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden;">

<div style="color: white;">

<div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 15px; margin: 20px 0;">

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; backdrop-filter: blur(10px); border: 1px solid rgba(255,255,255,0.2);">

**C++17**  
Основной язык программирования

</div>

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; backdrop-filter: blur(10px); border: 1px solid rgba(255,255,255,0.2);">

**Qt6 Widgets**  
Фреймворк для графического интерфейса

</div>

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; backdrop-filter: blur(10px); border: 1px solid rgba(255,255,255,0.2);">

**qmake**  
Система сборки

</div>

<div style="background: rgba(255,255,255,0.15); padding: 15px; border-radius: 10px; backdrop-filter: blur(10px); border: 1px solid rgba(255,255,255,0.2);">

**Файловое хранилище**  
Текстовые файлы для персистентности

</div>

</div>

### 📚 Используемые компоненты Qt

<div style="background: rgba(255,255,255,0.1); padding: 15px; border-radius: 10px; margin: 15px 0; border-left: 3px solid rgba(255,255,255,0.5);">

- `QMainWindow` — главное окно приложения
- `QTableView` — таблицы для отображения данных
- `QDialog` — модальные диалоги
- `QScrollArea` — прокручиваемые области
- `QGridLayout` — сетка для карточек автомобилей
- `QShortcut` — горячие клавиши
- `QFileDialog` — диалоги выбора файлов

</div>

</div>

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%F0%9F%93%9D%20%D0%A4%D0%BE%D1%80%D0%BC%D0%B0%D1%82%20%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden;">

<div style="color: white;">

### 📄 Структура файлов

<div style="background: rgba(255,255,255,0.15); padding: 20px; border-radius: 15px; margin: 15px 0; box-shadow: 0 4px 8px rgba(0,0,0,0.2); border-left: 5px solid rgba(255,255,255,0.6); backdrop-filter: blur(10px);">

#### 📁 cars.txt
```csv
Brand,Model,Year,Price,Color,Horsepower,Transmission,Reserved,ReservedBy,Stock,VIN,ImagePath,Options
BMW,3 Series,2023,45000,Black,300,Automatic,0,,5,WBABC12345,images/car_bmw_3-series.jpg,Leather Seats:1500;Sunroof:2000
```

</div>

<div style="background: rgba(255,255,255,0.15); padding: 20px; border-radius: 15px; margin: 15px 0; box-shadow: 0 4px 8px rgba(0,0,0,0.2); border-left: 5px solid rgba(255,255,255,0.6); backdrop-filter: blur(10px);">

#### 👥 clients.txt
```csv
Full Name,Phone,Balance
John Doe,+1234567890,50000.00
```

</div>

<div style="background: rgba(255,255,255,0.15); padding: 20px; border-radius: 15px; margin: 15px 0; box-shadow: 0 4px 8px rgba(0,0,0,0.2); border-left: 5px solid rgba(255,255,255,0.6); backdrop-filter: blur(10px);">

#### 💰 sales.txt
```csv
CarData,ClientData,Date,OriginalPrice,FinalPrice,Discount1,Discount2
[сериализованные данные автомобиля],[сериализованные данные клиента],2024-01-15,45000.00,40500.00,10.0,0.0
```

</div>

</div>

</div>

<div align="center" style="position: relative; margin: 30px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=12,18,25&height=180&section=header&text=%F0%9F%8E%A8%20%D0%A1%D0%BA%D1%80%D0%B8%D0%BD%D1%88%D0%BE%D1%82%D1%8B&fontSize=42&fontColor=fff&animation=twinkling&fontAlignY=35"/>

</div>

<div style="background: linear-gradient(90deg, #d4a574 0%, #c97d60 25%, #b85a7e 50%, #9d4ba3 75%, #7b2cbf 100%); padding: 30px; border-radius: 0; margin: -20px 0 30px 0; box-shadow: 0 15px 40px rgba(123, 44, 191, 0.4); position: relative; overflow: hidden; text-align: center;">

<div style="color: white;">

> *Примечание: Добавьте скриншоты интерфейса приложения для лучшей визуализации*

</div>

</div>

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=100&section=footer&text=%20&animation=twinkling"/>

</div>


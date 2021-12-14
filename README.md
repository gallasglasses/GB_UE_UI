# GB_UE_UI
 Learning how to create, display, and remove UI elements from the screen during gameplay.
 
 
I used the UE-Only Content (UE-Only Content - Licensed for use only with and under the same terms as the Unreal Engine.) 
for educational purposes such as :

[Paragon: Terra](https://www.unrealengine.com/marketplace/en-US/product/paragon-terra?sessionInvalidated=true)

![Alt-текст](https://cdn1.epicgames.com/ue/product/Screenshot/TerraScreenshot3-1920x1080-8d471a8dd9d9c47f1c895ec87969ba3c.png?resize=1&w=1920 "Paragon: Terra")

[Infinity Blade: Ice Lands](https://www.unrealengine.com/marketplace/en-US/product/infinity-blade-ice-lands)

![Alt-текст](https://cdn1.epicgames.com/ue/product/Screenshot/IBIceLandsScreenshot02-1920x1080-70b0965fef3dd34e9554d94b07cd0748-1920x1080-c3ce4b241da459f4d0d01c800e83d8dc.png?resize=1&w=1920 "Infinity Blade: Ice Lands")

## Урок 1. UMG: Знакомство

- [X] 1. Собрать виджет с центрированной надписью “Game Over” на красном фоне.
- [X] 2. Вывести виджет на экран, когда игрок умирает (или происходит другое игровое событие, НЕ нажатие на кнопку).
- [X] 3. (**)Cделать виджет красивым: заменить однотонный фон картинкой, использовать Rich Text Block вместо обычного текста.

[![Video HW1 part 1](https://img.youtube.com/vi/nYGZpavuhPo/0.jpg)](https://youtu.be/nYGZpavuhPo)
[![Video HW1 part 2](https://img.youtube.com/vi/GuoBnh1abMk/0.jpg)](https://youtu.be/GuoBnh1abMk)

## Урок 2. UMG базовые виджеты и их особенности

- [X] 1. Собрать виджет для главного меню
- [X] 2. Собрать виджеты статусов танка и врагов, виджет для отображения здоровья над танком
- [X] 3. (**)добавить анимации в виджеты
- [X] 4. (**)посмотреть различные примеры UI в библиотеке и повторить понравившиеся: https://www.gameuidatabase.com/index.php

[![Video HW2 part 1](https://img.youtube.com/vi/MycVuXNiSYI/0.jpg)](https://youtu.be/MycVuXNiSYI)
[![Video HW2 part 2](https://img.youtube.com/vi/geYGP1RkwXU/0.jpg)](https://youtu.be/geYGP1RkwXU)

## Урок 3. UMG. Привязка виджетов в С++ и создание менеджера виджетов

- [X] 1. Написать на C++ логику для созданных после предыдущего урока виджетов: главного меню, статусов танка и врагов.
- [X] 2. Отображать над танком и врагами полоски хп, показывающие актуальный уровень здоровья.
- [X] 3. (**)создать HUD менеджер, управляющий отображением главного меню, “Game Over” виджета, статуса своего танка.

[![Video HW3 part](https://img.youtube.com/vi/UyD73WaXxMI/0.jpg)](https://youtu.be/UyD73WaXxMI)

## Урок 4. Slate: Основы инициализация классов и передача аргументов

- [ ] 1. Создать виджет для мини карты, в котором переопределить метод OnPaint и с помощью MakeLines и MakeBox рисовать схематическую карту уровня.
- *(Не использована функция MakeLines)
- [X] 2. Добавить изображение позиции игрока на мини-карту.
- [X] 3. (**)сделать карту динамической, обновляя при передвижении игрока.
- [ ] 4. (**)снова заглянуть в библиотеку и реализовать любой виджет, для которого UMG было недостаточно: https://www.gameuidatabase.com/index.php

[![Video HW4 part 1](https://img.youtube.com/vi/rnWolczr-ow/0.jpg)](https://youtu.be/rnWolczr-ow)
[![Video HW4 part 2](https://img.youtube.com/vi/ogJ-yzVk_PA/0.jpg)](https://youtu.be/ogJ-yzVk_PA)

## Урок 5. Slate: Стили

- [X] 1. Создать стили для уже имеющихся в проекте umg виджетов.
- [X] 2. Создать несколько цветовых тем и применить их.
- [ ] 3. (**)сделать и применять стиль к мини-карте.

[![Video HW5](https://img.youtube.com/vi/u7loNA-ccAg/0.jpg)](https://youtu.be/u7loNA-ccAg)

## Урок 6. Slate и UMG: Drag&Drop

- [X] 1. Создание нескольких типов объектов для ДрагДропа
- [X] 2. Во время игры есть возможность вызвать список доступных объектов и ДрагДропом перетащить в мир
- [X] 3. при наведении на объект в списке появляется попап (виджет) с информацией о нём
- [X] 4. (**)доработать ДрагДроп так, чтоб перетаскиваемый виджет вставлялся до виджета, над которым находится, если курсор находится над верхней половиной виджета, и после - если над нижней

[![Video HW6 part 1](https://img.youtube.com/vi/w_X9RQixANI/0.jpg)](https://youtu.be/w_X9RQixANI)
[![Video HW6 part 2](https://img.youtube.com/vi/KXSEFxBYaRc/0.jpg)](https://youtu.be/KXSEFxBYaRc)

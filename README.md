# Устройство термостабилизации и управления магнитом для химической установки

### Команды интерфейса управления по UART

Форматирование окончания строки `\r\n`.

`-T 1000` задать период выдачи данных о температуре, подаваемой мощности на нагреватели и магнит в миллисекундах;

`-t 150` задать температуру поддержания в градусах по цельсию;

`-o 10.20` задать постоянное смещение температуры;

`-a 1` включить режим автоподдержания температуры (0 - выключен, 1 - включен);

`-M 80` задать мощность, подаваемую на магниты в процентах;

`-q 150.0 30` задать температуру и время, в течение которого она должна быть достигнута. Первый параметр - температура (в формате с точкой), второй - время в минутах, целочисленный. При этом температура от времени будет меняться по линейному закону.

`-p 0.01` задать коэффициент P ПИ-регулятора;

`-i 0.01` задать коэффициент I ПИ-регулятора;

`-P` вывести текущие настройки;

`-s` сохранить текущие настройки в энергонезависимую память (коэффициенты ПИ-регулятора, период выдачи данных, смещение температуры)
# Практическая работа 2.1

## Знакомство с библиотекой Qt

Разработано графическое приложение для взаимодействия с программой openssl. 
Окно приложения содержит два выпадающих списка, расположенных в ряд, которые 
позволяют выбрать алгоритм шифрования, а также соответствующий ему алгоритм 
хеширования. Ниже, друг под другом, располагаются поля для ввода значений 
запроса сертификата и кнопка. Под кнопкой располагается текстовое поле. 
При нажатии на кнопку происходит создание запроса сертификата, при этом 
закрытый ключ сохраняется в файл private.key, а сам запрос отображается в 
текстовом поле.

### Примечания
В качестве основного класса окна приложения использован QWidget. 
Для размещения элементов окна задействованы QHBoxLayout и QVBoxLayout.
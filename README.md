# BrickGame

Реализация brick_game под Qt.


Основу всей программы составляют 3 класса:

screen - представляет собой представление игры на экране

abstractGame - базовый класс для игры

general_window - окно, в котором открывается программа


Используется система ресурсов для всех сторонних данных. Используются 
stylesheets.


Все важные константы собраны в файле brick_game.hpp. Это:

  FIELD_SIZE - размеры поля

  MINI_FIELD_SIZE - размеры маленького поля в screen

  MINI_SCR_BGN - начало отсчета значений brick_game::point для мальнького поля

  Value - допустимые значения для поля (ИСПОЛЬЗУЙТЕ ТОЛЬКО ИХ)

  Direction - значения, которые пересылаются с событиями в custormEvent

  Event - евенты (не заморачивайтесь)

  LEVEL_DIGIN_COUNT - количество цифр для уровня (не более 99)

  SCORE_DIGIN_COUNT - количество цифр для очков (не более 999 999)

  HOME - каталог для хранения файлов
  

===============================================================================

Встречайте: класс abstractGame

Для того, чтобы избежать подключения коннектов каждый раз при установке новой
игры следует наследовать abstractGame который автоматически подключается к 
screen после вызова screen.set_game().


Переменные:

  std::vector<std::vector<Value>> field_ - это поле с которым вам придется работать.
    Изначально не инициализировано!!!

  bool soundless_ - если равно true то нельзя воспроизводить звук (проверка 
    ложится на РАЗРАБОТЧИКА игры, тобишь на Вас)

  ::QMediaPlayer player_ - медиа плэер (в случае получения сигнала об отключении
    звука прекращает воспроизведение)


Вам нужно переопределить несколько методов и слотов (см в abstractGame.hpp).

Методы:

  customEvent(::QEvent *) - использует события для управление игрой (смотрите пример
    реализации simpleExempl)

  game_name() - возвращает имя игры (БЕЗ ПРОБЕЛЬНЫХ СИМВОЛОВ!!!)


Слоты:

  start_game_slot() - запускает вашу игру

  finish_game_slot() - завершает вашу игру

  remove_sound_slot() - переставляет значение soundless_  на противоположное и
    останавливает любое воспроизведение через player_


Также в этом классе имеются следующие сигналы, которые следует использовать для
общения с screen:

  changed(::QPoint, Value) - отсылает сигнал об изменении ОДНОГО элемента поля

  end_game_signal(unsigned short, unsigned) - отсылает сигнал о том, что игра была прекращена и
    пересылает значения level и score (по умолчанию пересылает 0-и)

  send_level(int) - отсылает значение уровня

  send_score(int) - отсылает значение очков

  pause_signal() - если ваша игра поддерживает паузу, то высылайте этот сигнал
    после постановки на паузу


Статические методы:

  END_FIELD() - возвращает значение класса brick_game::point преобразованное из размера
    FIELD_SIZE() или правый нижний угол screen (за пределами поля)

  RBEGIN_FIELD() - возвращает значение класса brick_game::point являющееся 
    левым верхним углом screen (за пределами поля)

Они нужны для удобной проверки находится ли объект в пределах поля? (смотрите 
класс brick_game::point)


Имеется также не виртуальный метод 
  
  bool is_passible(brick_game::point) - простая реализация проверки выхода за
    пределы поля


===============================================================================


Пара слов о brick_game::point

Класс специально создан для легкого определения выхода за пределы поля. Для
этого у него определены операторы < и >. Работают они исходя из 2 и 4 четверти.
Тобишь, если правое значение находится во 2-ой четверти относительно левого, то
оно больше левого значения, и наоборот. Но ТОЛЬКО ДЛЯ 2-й и 4-й четвертей.

Автоматически приводится к ::QPoint


===============================================================================


Пара слов о screen

Вам следует знать, что метод set_game - не передает владение объектом вашей 
игры screen!

Также, следует знать, что таблица рекордов в конце игры появляется только в
случае передачи сигнала из игры end_game_siganl. Поэтому в случае завершения
вашей игры принудительно (через screen) следует указать следующую конструкцию:

if (sender() != this) {
  emit end_game_signal(level, score);
  return;
}


===============================================================================


Для добавление созданной игры следует в классе general_window добавить ::QAction
с соответствующим названием в меню Games и связать ваш QAction с лямдой, которая
ОЧИСТИТ предыдущую игру и установит вашу в указатель cur_game_, после чего 
вызвать метода screen.set_game с указателем на вашу игру.

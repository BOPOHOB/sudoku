# Вебвью кибермонтиоринга

## Запуск

1. Установите [nvm](https://github.com/nvm-sh/nvm) ([подробнее на русском](https://habr.com/ru/company/timeweb/blog/541452/))
1. Настройте [editorconfig](https://editorconfig.org/) в вашем редакторе кода
1. Туда же [проверку правописания](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker) + [русификатор](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker-russian) (md пишем на русском, комменты по месту стараемся на английском)
1. Настройте `nvm use` чтобы выполнялся автоматически. Проще всего сделать как [тут](https://stackoverflow.com/a/48322289/7634570)
1. `sudo apt install tmux && echo "set -g mouse on" >> ~/.tmux.conf` - утилита нужна чтобы запускать одной командой сразу и _frontend for backend_ и _front_
1. Теперь можно прогнать `npm install`
1. `npm start` - это запустит окно, в котором развернутся две консоли для бека и для фронта
1. Если `tmux` настроить не получается то можно использовать `npm run webpack` и `npm run nest`
1. Чтобы правильно анализировался typescript в vscode можно выполнить [совет со stack overflow](https://stackoverflow.com/a/67450669/7634570)

## Тесты

### Юниты

Сейчас на проекте пишутся только юниты, они и линтеры выполняются перед каждым пушом. Тесты пишутся не ради полного покрытия (оно ничего не гарантирует). Покрываем тестами только ту логику, которую очень редко трогаем, которая сформулирована в виде алгоритма и в которую легко посадить ошибки

### End-to-end

[Кликеры](https://playwright.dev/) пока писать мотивации нет, надеемся на то, что всё будет написано классно и дополнительного тестирования не понадобится

## Backend for frontend

Фронтенд не ходит в бэкенд напрямую, все запросы проходят через _backend for frontend_-сервер. Это [stateless](https://medium.com/@ermakovichdmitriy/%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F-%D0%BF%D0%BE%D0%BD%D1%8F%D1%82%D0%B8%D0%B9-stateful-%D0%B8-stateless-%D0%B2-%D0%BA%D0%BE%D0%BD%D1%82%D0%B5%D0%BA%D1%81%D1%82%D0%B5-%D0%B2%D0%B5%D0%B1-%D1%81%D0%B5%D1%80%D0%B2%D0%B8%D1%81%D0%BE%D0%B2-%D0%BF%D0%B5%D1%80%D0%B5%D0%B2%D0%BE%D0%B4-18a910a226a1) сервер, выполняющий роль прослойки между беком и фронтом.
Такая абстракция даёт
1. Отвязку логики написания backend-ручек от потребностей фронтенда. Мы можем не предъявлять к бэкенду требований, мотивированных представлением данных а не их структурой
1. Возможность серверной интеграции с сервисами напрямую, освобождая бек от простых пробросов, повышая прозрачность и масштабируемость системы
1. Возможность кеширования ([холодные](https://www.section.io/blog/what-is-cache-warming/) [in memory кеши](https://docs.nestjs.com/techniques/caching))

## Стейт

### [Сторы](https://mobx.js.org/defining-data-stores.html#ui-stores) (домены)

Время жизни стора определяется областью его применения. Основные сторы - `Global` и `Session`. `Global` провайдится на всё приложение и существует всегда. `Session` создаётся в `AuthorizedRouter` и существует всё время пока пользователь авторизован (почти всегда).

### `null`, `undefined`, value - соглашение
Всё что не загружено должно помечаться как `undefined`, всё, что не задано помечается как `null`, отдельно в явном виде загрузка не запрашивается. Если данные запрошены то они должны немедленно начинать загружаться, если отсутствуют.

### Формы

Формы не должны использовать стор. При использовании формы правильно скопировать данные из стора и только потом положить их в форму. По [сабмиту](https://learn.javascript.ru/forms-submit) из формы данные передаются стору, стор дёргает сервис, сервис запрашивает обновление на сервере, сервер репортит об успешном обновлении, сервис резолвит [промис](https://learn.javascript.ru/promise), стор обновляется и триггерит перерисовку виджетов.

Позитивное обновление запрещено так как закрывает возможность сообщить пользователю что данные успешно обновлены. Можно не дизейблить дальнейший сценарий но у тебя обязательно должны висеть лоадеры где-то до тех пор пока данные не обновятся.

## Git flow

1. Любая задача является отдельной веткой. В ветку вливаются коммиты, каждый коммит описывается по форме `CYBER-3333: commit message`
2. Когда задача выполнена, с точки зрения программиста всё в порядке можно начинать ревью. После ревью вливаются дальшейшие правки, если всё хорошо и правок больше нет то ветка вливается в мастер.
3. В мастер надо вливать примерно так: `git pull && git rebase origin/master && git checkout master && git merge -ff-only branch-name && git push`

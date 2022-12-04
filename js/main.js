window.onload = function () {
  function load() {
    let preloader = document.getElementsByClassName('preloader')
    preloader.style.visibility = 'hidden'
    preloader.style.opacity = '0'
    document.querySelector('body').style.overflowX = 'visible'
    document.querySelector('body').style.overflowY = 'visible'
  }

  const state = document.querySelectorAll('.state')
  const system = document.querySelectorAll('.table__grid')
  const popupBG = document.querySelector('.popup__bg')
  const form = document.querySelector('.search-form')
  const numbersOfSystems = document.querySelectorAll('.numberSystem')
  const filterOn = document.getElementById('filter-on')
  const filterOff = document.getElementById('filter-off')

  state.forEach((el) => {
    // Определяет цвет состояния объекта
    if (el.innerHTML == 'Авария') {
      el.classList.add('state_off')
    } else if (el.innerHTML == 'В работе') {
      el.classList.add('state_on')
    }
  })

  function popup() {
    // Отображение и скрытие попапа
    system.forEach((item) => {
      item.addEventListener('click', () => {
        let popup = item.querySelector('.popup')
        popupBG.classList.add('popup__on')
        popup.classList.add('popup__on')
        let popupClose = item.querySelector('.close')
        console.log(popupClose)
        popupClose.addEventListener('click', () => {
          event.stopPropagation() // Запрет всплытия, иначе при нажатии потоврно навешивает класс
          popupBG.classList.remove('popup__on')
          popup.classList.remove('popup__on')
        })
      })
    })
  }

  function filter(ev) {
    ev.preventDefault()
    const input = document.querySelector('#system-search')
    const inputValue = input.value.replace(/\D/g, '') // Получает только цифры введенные в поле поиска
    numbersOfSystems.forEach((item) => {
      let numberSystem = item.innerHTML // Получаем номер системы
      let parentNumber = item.closest('.table__item') // Ищем родителя чтобы скрыть другие
      if (numberSystem.includes(inputValue)) {
        parentNumber.classList.add('.show_search')
        parentNumber.classList.remove('.hidden_search')
      } else {
        parentNumber.classList.add('hidden_search')
        parentNumber.classList.remove('show_search')
      }
    })
  }
  function filterReset() {
    const input = document.querySelector('#system-search')
    numbersOfSystems.forEach((item) => {
      let parentNumber = item.closest('.table__item')
      if ((input.value == null, input.value == '')) {
        parentNumber.classList.remove('hidden_search')
      } else {
        return
      }
    })
  }
  // Фильтры состояния checkbox start
  function filterState() {
    const StateSet = new Set() // Множество для хранения состояния нажатых checkbox
    filterOn.addEventListener('click', () => {
      state.forEach((el) => {
        let parentState = el.closest('.table__item')
        if (filterOn.checked && el.innerHTML == filterOff.value) {
          parentState.classList.add('hidden_check')
          StateSet.add(el.innerHTML)
        } else if (
          filterOn.checked === false &&
          el.innerHTML == filterOff.value
        ) {
          parentState.classList.remove('hidden_check')
          StateSet.delete(el.innerHTML)
        }
        if (StateSet.size == 2) {
          // При одновременном нажатии двух checkbox, сбрасывает их
          state.forEach((el) => {
            let parentState = el.closest('.table__item')
            parentState.classList.remove('hidden_check')
          })
          if (filterOn.checked && filterOff.checked) {
            filterOn.checked = false
            filterOff.checked = false
          }
          StateSet.clear()
        }
      })
    })
    filterOff.addEventListener('click', () => {
      state.forEach((el) => {
        let parentState = el.closest('.table__item')
        if (filterOff.checked && el.innerHTML == filterOn.value) {
          parentState.classList.add('hidden_check')
          StateSet.add(el.innerHTML)
        } else if (
          filterOff.checked === false &&
          el.innerHTML == filterOn.value
        ) {
          parentState.classList.remove('hidden_check')
          StateSet.delete(el.innerHTML)
        }
        if (StateSet.size == 2) {
          state.forEach((el) => {
            let parentState = el.closest('.table__item')
            parentState.classList.remove('hidden_check')
          })
          if (filterOn.checked && filterOff.checked) {
            filterOn.checked = false
            filterOff.checked = false
          }
          StateSet.clear()
        }
      })
    })
  }
  // Фильтры состояния checkbox end

  form.addEventListener('keyup', filter)
  form.addEventListener('keyup', filterReset)
  filterState()
  popup()
  load()
}
alert('ddd')

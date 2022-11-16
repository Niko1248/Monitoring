const systemsContainer = document.querySelector('#table-systems');

getSystems();

async function getSystems() {
  //получаем массив из json в котором мы определили массив
  //обязательно через await,необходимо достоверно получить данные
  const response = await fetch('./js/systems.json')
  //присваиваем хначение массива переменной
  const systemsArray = await response.json()
  //теперь передаем этоту переменную с массивом в другую функцию
	renderSystems(systemsArray)
}

function renderSystems(systemsArray) {
  //пербираем все элементы в массиве и вставляем их в шаблон
  systemsArray.forEach(function (item) {
    const systemHTML = `<div class="table__item table__grid">
												<div>${item.id}</div>
												<div>${item.number}</div>
												<div>${item.priority}</div>
												<div>${item.correspondent}</div>
												<div>${item.type}</div>
												<div class="state">${item.state}</div>
												</div>`
		    //вставляем шаблон в страницу(отрисовываем)
    systemsContainer.insertAdjacentHTML('beforeend', systemHTML)
  })
}

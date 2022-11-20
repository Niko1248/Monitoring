const systemsContainer = document.querySelector('#table-systems');

getSystems();

async function getSystems() {
  //получаем массив из json в котором мы определили массив
  //обязательно через await,необходимо достоверно получить данные
  const response = await fetch('./js/systems.json')
  //присваиваем значение массива переменной
  const systemsArray = await response.json()
  //теперь передаем этоту переменную с массивом в другую функцию
	renderSystems(systemsArray)
}

function renderSystems(systemsArray) {
  //перебираем все элементы в массиве и вставляем их в шаблон
  systemsArray.forEach(function (item) {
    const systemHTML = `<div class="table__grid">
													<div class="table__item">
														<div>${item.id}</div>
														<div class="number">${item.number}</div>
														<div>${item.priority}</div>
														<div>${item.correspondent}</div>
														<div>${item.type}</div>
														<div class="state">${item.state}</div>
													</div>
													<div class="popup__wrapper">
														<div class="popup">
															<div class="close">
																<a class="close__img">
																	<img src="./img/close.png" alt="" />
																</a>
															</div>
															<div class="popup__content">
																<div>Трасса: </div>
																<div>Каналы: </div>
																<div>Что-нибудь еще: </div>
															</div>
														</div>	
													</div>			
												</div>`
		    //вставляем шаблон в страницу(отрисовываем)
    systemsContainer.insertAdjacentHTML('beforeend', systemHTML)
  })
}

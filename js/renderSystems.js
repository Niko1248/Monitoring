const systemsContainer = document.querySelector('#table-systems')

getSystems()

async function getSystems() {
  //получаем массив из json в котором мы определили массив
  //обязательно через await,необходимо достоверно получить данные
  const response = await fetch('./js/systems.xml')
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
	<div class="row-number"></div>
	<div class="numberSystem">${item.numberSystem}</div>
	<div>${item.priority}</div>
	<div>${item.correspondent}</div>
	<div>${item.type}</div>
	<div class="state">${item.state}</div>
</div>
<div class="popup__wrapper">
	<div class="popup">
		<div class="close">
			<a class="close__img">
				<img src="./img/close.png" alt="" / style="width:23px;height:23px;transition:0.4s;">
				<style>
				.close__img>img:hover{
					transform:rotate(360deg);
					transition:0.4s;
				}
				</style>
			</a>
		</div>
		<div class="popup__content">
			<div>Трасса: 
			${item.cor1}
			${item.SL1}
			${item.cor2}
			${item.SL2}
			${item.cor3}
			${item.SL3}
			${item.cor4}																
			</div>
			<div class="popup__content-down">
			<div>Загрузка: 
																		
			</div>
			<div class="popup__state"> Состояние: ${item.state} </div
			</div>
		</div>
	</div>	
</div>			
</div>`
    //вставляем шаблон в страницу(отрисовываем)
    systemsContainer.insertAdjacentHTML('beforeend', systemHTML)
  })
}

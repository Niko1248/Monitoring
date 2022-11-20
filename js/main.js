window.onload = function (){
	const state = document.querySelectorAll('.state');
	const system = document.querySelectorAll('.table__grid');
	const popupBG = document.querySelector('.popup__bg');
	
	state.forEach(el => {				// Определяет цвет состояния объекта
		if (el.innerHTML == 'Авария'){
			el.classList.add('state_off');
		}else{
			el.classList.add('state_on');
		}
	});
	system.forEach(item => {			// Отображение и скрытие попапа
		item.addEventListener("click", () => {
			let popup = item.querySelector('.popup__wrapper');
			popupBG.classList.add('popup__on');
			popup.classList.add('popup__on');
			let popupClose = item.querySelector('.close');
			console.log(popupClose);
			popupClose.addEventListener('click', () => {
				event.stopPropagation();
				popupBG.classList.remove('popup__on');
				popup.classList.remove('popup__on');
			})
		})
	})
}


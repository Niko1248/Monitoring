window.onload = function (){
	const state = document.querySelectorAll('.state');
	const system = document.querySelectorAll('.table__grid');

	state.forEach(el => {
		if (el.innerHTML == 'Авария'){
			el.classList.add('state_off');
		}else{
			el.classList.add('state_on');
		}
	});
	system.forEach(item => {
		item.addEventListener("click", () => {
			let popup = item.querySelector('.popup__bg');
			popup.classList.add('popup__on');
			let popupClose = item.querySelector('.close');
			popupClose.addEventListener('click', () => {
				popup.classList.remove('popup__on');
			})
		})
	})
}


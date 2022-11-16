window.onload = function (){
	const state = document.querySelectorAll('.state');
	state.forEach(el => {
		if (el.innerHTML == 'Авария'){
			el.classList.add('state_off');
		}else{
			el.classList.add('state_on');
		}
	});
}


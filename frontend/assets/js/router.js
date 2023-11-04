
function rte(url) {
	let pg = url.split('/').pop()
	let hh = window.location.hash

	if (pg==='') {
		if (Pge===1) {return}
		Pge=1
		if (loggedIn) {
			Ga.className = 'showRate';
			clearMn(Mn)
			getRater()
		} else {
			Ga.className = 'showLogin';
		}
	} else if (pg==='tasks') {
		if (Pge===2) {return}
		
		Ga.className = 'showTasks';
		clearMn(Mn)
		
		let limit = 0
		let offset = 0
		
		getAllTests()
		Pge=2
	} else if (pg==='taskID') {
		if (Pge===3) {return}
		clearMn(Mn)
		
		Ga.className = 'showTaskID';
		let taskID = 1
		Pge=3

		getTestID()
	} else if (pg==='imageID') {
		if (Pge===4) {return}
		clearMn(Mn)
		
		Ga.className = 'showTasks showImg';
		let taskID = 1
		Pge=4
		generateImage();
	} else if (pg==='profile') {
		if (Pge===5) {return}
		clearMn(Mn)
		
		genPrf()
		Pge=5
		Ga.className = 'showProfile edit';
	} else if (pg==='security') {
		if (Pge===6) {return}
		clearMn(Mn)
		
		Pge=6
		Ga.className = 'showProfile sec';
	} else if (pg==='alerts') {
		if (Pge===7) {return}
		clearMn(Mn)
		
		Pge=7
		Ga.className = 'showProfile alr';
	} else if (pg==='billing') {
		if (Pge===8) {return}
		clearMn(Mn)
		
		Pge=8
		Ga.className = 'showProfile bil';
	} else if (pg==='help') {
		if (Pge===9) {return}
		clearMn(Mn)
		
		Pge=9
		Ga.className = 'showProfile hlp';
	} else if (pg==='login') {
		if (Pge===10) {return}
		clearMn(Mn)
		
		Pge=10
		Ga.className = 'showLogin';
		genLogin()
	} else if (pg==='signup') {
		if (Pge===11) {return}
		clearMn(Mn)
		
		Ga.className = 'showSignup';
	} else if (pg==='statistics') {
		if (Pge===19) {return}
		clearMn(Mn)
		
		Ga.className = 'showTaskID';
		let taskID = 1
	} else if (pg==='notifications') {
		if (Pge===23) {return}
		clearMn(Mn)
		
		Pge=23
		Ga.className = 'showNotifications';
	} else if (pg==='paired') {
		if (Pge===12) {return}
		clearMn(Mn)
	
		console.log(Mn)
		Pge=12
		getPaired()
		Ga.className = 'showPaired';
	} else if (pg==='premium') {
		if (Pge===155) {return}
		clearMn(Mn)
		
		Ga.className = 'showPremium';
		Pge=155
	} else if (pg==='r2') {
		Ga.className = 'showR2';
		Pge=33
	} else {
		alert('phucc')
	}

}



function pth() {
	rte(window.location.pathname)
	window.history.pushState({},window.location.pathname,window.location.pathname)
}


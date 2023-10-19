
// dropdown for aux icons in nav
let auxIconData = {
	que: false,
	nof: false,
	prf: false,
	pls: false
};

// hamburger for main menu in nav
function s() {

}
var loggedIn = true
let W=window
let Pge=-1

window.onhashchange = function() {
 //blah blah blah
	alert('hashchange')
}

window.onpopstate = function(event) {
	alert('back or forward triggered')
	rte(event.target.location.pathname)
}


function rte(url) {
	let pg = url.split('/').pop()
	let hh = window.location.hash

	if (pg==='') {
		Pge=1
		if (loggedIn) {
			Ga.className = 'showRate';
			
			let rtx = getRater()
			document.body.insertBefore(rtx, document.body.firstChild);
		} else {
			Ga.className = 'showLogin';
		}
	} else if (pg==='tasks') {
		console.log('tasks yee')
		Ga.className = 'showTasks';
		let limit = 0
		let offset = 0
		getAllTests()
		Pge=2


	} else if (pg==='taskID') {
		Ga.className = 'showTaskID';
		let taskID = 1
		Pge=3

		getTestID()
	} else if (pg==='imageID') {
		Ga.className = 'showTasks showImg';
		let taskID = 1
		Pge=4

		for (let i = 0; i < 1; ++i) {
			imageIndiv()
		}
	} else if (pg==='profile') {
		Pge=5
		Ga.className = 'showProfile edit';
	} else if (pg==='security') {
		Pge=6
		Ga.className = 'showProfile sec';
	} else if (pg==='alerts') {
		Pge=7
		Ga.className = 'showProfile alr';
	} else if (pg==='billing') {
		Pge=8
		Ga.className = 'showProfile bil';
	} else if (pg==='help') {
		Pge=9
		Ga.className = 'showProfile hlp';
	} else if (pg==='login') {
		Pge=10
		Ga.className = 'showLogin';
	} else if (pg==='signup') {
		Ga.className = 'showSignup';
	} else if (pg==='statistics') {
		Ga.className = 'showTaskID';
		let taskID = 1
	} else if (pg==='notifications') {
		Pge=11
		Ga.className = 'showNotifications';
	} else if (pg==='paired') {
		let Prd=getPaired()
		Pge=12
		document.body.insertBefore(Prd, document.body.firstChild);
		Ga.className = 'showPaired';
	} else if (pg==='premium') {
		Ga.className = 'showPremium';
	} else if (pg==='r2') {
		Ga.className = 'showR2';
		Pge=33
	} else {
		alert('phucc')
	}

	//window.history.pushState({},e.target.href,e.target.href)
}

function pth() {
	
}

rte(window.location.pathname)
window.history.pushState({},window.location.pathname,window.location.pathname)


var OPN = -1 // this represents the id that is opened
var FIL = -1 // controls if filter is open

/*
  <ul id="zDropdown" class="dropsort">
	<li id="Sd0" class="noselect active">Delete test</li>
	<li id="Sd1" class="noselect active">Pause test</li>
	<li id="Sd2" class="noselect active">Restart test</li>
	<li id="Sd3" class="noselect active"> test</li>
  </ul>
*/


function removeDropdowns(idxv) {
	if (OPN==-1) {return true}

	switch (OPN) {
		case 1: // mobile hamburger menu for nav
			// previously was 'A'
			Na.className=''
		case 2: // logo dropdown
			// previously had 'A'
			Da.className='dropdown BlA'
		case 3: // nav notification dropdown
			// previously had 'A'
			dea.className='dropdown'
			break
		case 4: // profile dropdown
			// previously had 'A'
			dfa.className='dropdown'
			break
		case 5: // rate more dropdown (reports, etc)
			// previously had 'A'
			rMor.className='dropsort'
			break
		case 6: // dots for edit/delete task in /taskID
			// previously had 'A'
			Da.className='dropdown BlA'
			break
		case 7: // dots for edit/delete task in grid /tasks
			// previously had 'A'
			Da.className='dropdown BlA'
			break
		case 8: // sort dropdown for /tasks
			sortDropdown.className='dropsort'
			break
		case 9: // filter dropdown for /tasks
			Da.className='dropdown BlA'
			break
		case 10: // date dropdown in /profile
			DAT.className='dropdown BlA'
			break
		case 11: // language dropdown in /profile
			LNG.className='dropdown BlA'
			break
		case 100: // new test upload modal
			// previously was 'U'
			ZZ.className='A'
			break
		default:
			break
	}

	let ov = OPN
	OPN=-1
	return (idxv!==ov)
}


let cRate=-1
let cTg=0
let cLanguage=-1
let cStatus=0
let cSortVal=0

document.onclick = (e) => {
	let tG=e.target
	let H=e.target.id
	let key=H.slice(-1)
	console.log(H)

	// link
	if (key === '_') {
		event.preventDefault();
		rte(e.target.href)
		window.history.pushState({},e.target.href,e.target.href)
		removeDropdowns(-1)
	}

////// DARK 
	else if (tG == ZZ) {
		Ga.className=Ga.className.substr(10)
		
		alert('dark')
		Ga.className = 'showTasks'
		rte('/taskID')
		window.history.pushState({},'/taskID','/taskID')
	}

////// navigation #Na
	if (tG === Bc) {
		if (removeDropdowns(1)) {Na.className='A';OPN=1}
	}

	// logo dropdown
	else if (Lb.contains(tG)) {
		if (removeDropdowns(2)) {Da.className='dropdown BlA A';OPN=2}
	}

	// bell/notification
	else if (tG===Je||tG===Ke||tG===Le) {
		if (removeDropdowns(3)) {dea.className='dropdown BlA A';OPN=3}
	}

	// head/profile
	else if (tG===Jf||tG===Kf||tG===Lf) {
		if (removeDropdowns(4)) {dfa.className='dropdown BlA A';OPN=4}
	}

	// new test upload modal
	else if (tG===Pd) {
		alert('seg')
		if (removeDropdowns(-1)) {Ga.className+=' showUpl';OPN=100}
	}


////// / page (rater)

	// rating 
	else if (Pge===1) {
		if (Ca.contains(tG) && tG !== Ca) {
			let aidx=key - '0'
			if (cRate!==-1){Ca.children[cRate].className='btn BR';}
			Ca.children[aidx].className='btn BR A';
			cRate = aidx
		}

		// tag 
		else if (Ua.contains(tG) && tG !== Ua) {
			let aidx=key.charCodeAt(0) - 97
			//console.log(aidx)
			if (cTg&(1<<aidx)){Ua.children[aidx].className='BZ';cTg ^= (1<<aidx);}
			else{Ua.children[aidx].className='BZ A';cTg |= (1<<aidx);}
		}
		
		// dropdown
		else if (Dmo.contains(tG)) {
			console.log('69420')
			if (removeDropdowns(5)) {rMor.className='dropsort A';OPN=5}
		}

		// report
		else if (Rpt.contains(tG)) {
			console.log('report')
		}

		// skip
		else if (Sk.contains(tG)) {
			console.log('skip')
		}

		// submit
		else if (Sm.contains(tG)) {
			console.log('submit')
		}

	}

	else if (Pge===12) {

	////// /paired page
		if (IWa.contains(tG)) {
			console.log('pic a')
		}

		else if (IWb.contains(tG)) {
			console.log('pic b')
		}
	}

////// /tasks page

	// sort method in tests 
	//// NEED TO DEAL WITH THIS IN CONTEXT OF ROUTING BEHAVIOR
	else if (Pge===2) {

		/*
		if (tG === sortMethodV) {
			if (removeDropdowns(8)) {sortDropdown.className='dropsort show active A';OPN=8}
		}


		// view all regardless of task status
		else*/

		if (tflta.contains(tG) && tG !== tflta) { //a === vAll
			let aidx=key - '0'
			// make sure this is not 0 samples!
			if (cStatus!==aidx) {
				tflta.children[cStatus].className='btn'
				tflta.children[aidx].className='btn A'
				cStatus=aidx

				// refresh page
			}
		}
/*
		else if (sortDropdown.contains(tG) && tG !== sortDropdown) {
			let aidx=key - '0'

			sortMethodV.innerText = sortDropdown.children[aidx].innerText
			
			console.log('seg')
		}*/

	/*
		// view tasks of current run status
		else if (tG === vRun) {
		}

		// view tasks of paused status
		else if (tG === vPau) {
		}

		// view tasks of finished status
		else if (tG === vFin) {
		}
	*/
	}

	else if (Pge===3) {
		if (tG === dtz) {
			//if (removeDropdowns(8)) {sortDropdown.className='dropsort show active A';OPN=8}
		}
	}

////// /profile view
	else if (Pge>=5&&Pge<=9) {
		// email
		if (EiEml.contains(tG)) {
			console.log('same procedure as /rater tag')
		}

		// phone country code

		// phone edit
		else if (EiEml.contains(tG)) {
			console.log('same procedure as /rater tag')
		}

		// gender
		else if (pGda.contains(tG) && pGda !== tG) {
			console.log('same procedure as /rater tag')
		}

		// activity
		else if (pHbt.contains(tG) && pHbt !== tG) {
			console.log('same procedure as /rater tag')
			key -= '0'
			console.log(key)
			switch (key) {
				case 0:
					pHbt.children[0].style.left='0'
					break
				case 1:
					pHbt.children[0].style.left='110px'
					break
				case 2:
					pHbt.children[0].style.left='220px'
					break
				case 3:
					pHbt.children[0].style.left='330px'
					break
				case 4:
					pHbt.children[0].style.left='440px'
					break
			}
		}

		// dropdown for language
		else if (lndr.contains(tG)) {
			if (removeDropdowns(11)) {LNG.className='dropsort A';OPN=11}
		}

		// picked a language
		else if (LNG.contains(tG)) {
			console.log('picked language, same procedure as /rater tag, now remove dropdown and change language')
		}
	}

	// sign up
	else if (key == 'q') {
		rte('/')
		window.history.pushState({},'/','/')
	}

	// sign out
	else if (key == 'r') {
		console.log('seggs')
		rte('/login')
		window.history.pushState({},'/login','/login')
	}

	// status filter dropdown
	else if (key == 'y') {
		console.log('seg')
		stusDrop.classList.toggle('show')
	}

	// remove dropdowns,
	// this is click outside
	else {
		console.log('remove dropdown')

		removeDropdowns(999)
	}
	
	// report
	// skip
	// submit
	
	// check if any dropdowns are open

};














// oninputchange


/*

*/
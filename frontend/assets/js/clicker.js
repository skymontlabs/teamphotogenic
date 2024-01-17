let Mn=DIV.cloneNode(true)
Mn.id='Mn'

let xblk=DIV.cloneNode(true)
xblk.className='x'

Mn.appendChild(xblk)
Ga.appendChild(Mn)



// hamburger for main menu in nav
function s() {

}

let loaded=false
var loggedIn = true
let W=window
let Pge=-1

window.onhashchange = function() {
	alert('hashchange')
}

window.onpopstate = function(event) {
	alert('back or forward triggered')
	rte(event.target.location.pathname)
}

function rte(url) {
	let pg = url.split('/').pop()

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
		
		clearMn(Mn, true)
		Ga.className = 'showTasks';
		
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

pth()

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
			Da.className='dropdown BlA lk'
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
			Da.className='dropdown BlA lk'
			break
		case 7: // dots for edit/delete task in grid /tasks
			// previously had 'A'
			Da.className='dropdown BlA lk'
			break
		case 8: // sort dropdown for /tasks
			sortDropdown.className='dropsort'
			break
		case 9: // filter dropdown for /tasks
			Da.className='dropdown BlA lk'
			break
		case 10: // date dropdown in /profile
			DAT.className='dropdown BlA lk'
			break
		case 11: // language dropdown in /profile
			LNG.className='dropdown BlA lk'
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

results = []


function clearRater() {
	if (cRate !== -1) {
		Ca.children[cRate].className='btn BR';
		cRate = -1
	}

	if (cTg) {
		for (let i = 0; i < 17; ++i) {
			Ua.children[i].className='BZ';
		}
		cTg = 0
	}

	CMa.value = ''
	console.log('submit')
}

function storeResults() {

	// rating
	if (cRate !== -1) {
		Ca.children[cRate].className='btn BR';
		cRate = -1
	} else {
		// this is a must
		return -1
	}



	// tag
	if (cTg) {
		for (let i = 0; i < 17; ++i) {
			Ua.children[i].className='BZ';
		}
		cTg = 0
	}
	results.push(cTg)




	CMa.value = ''
	console.log('storeResults')
	return 0
}


let cRate=-1
let cTg=0
let cLanguage=-1
let cStatus=0
let cSortVal=0

let cPair=-1

let signupStatus=0

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
		// if this is, due to uploader, just simply remove it
		if (!removeDropdowns(100)) {
			Ga.className=Ga.className.substr(0, Ga.className.length - 8)
		} else {
			/*
			Ga.className = 'showTasks'
			rte('/taskID')
			window.history.pushState({},'/taskID','/taskID')*/
		}
	}

////// navigation #Na
	if (tG === Bc) {
		if (removeDropdowns(1)) {Na.className='A';OPN=1}
	}

	// logo dropdown
	else if (Lb.contains(tG)) {
		if (removeDropdowns(2)) {Da.className='dropdown BlA A lk';OPN=2}
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
		if (removeDropdowns(-1)) {
			Ga.className+=' showUpl';

			OPN=100;
			dropArea.addEventListener('drop', handleDrop, false)

			;['dragenter', 'dragover', 'dragleave', 'drop'].forEach(eventName => {
			  dropArea.addEventListener(eventName, preventDefaults, false)
			})

			;['dragenter', 'dragover'].forEach(eventName => {
			  dropArea.addEventListener(eventName, highlight, false)
			})

			;['dragleave', 'drop'].forEach(eventName => {
			  dropArea.addEventListener(eventName, unhighlight, false)
			})

		}
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
			console.log('dropdown report in rating')
			if (removeDropdowns(5)) {rMor.className='dropsort A';OPN=5}
		}

		// report
		else if (Rpt.contains(tG)) {
			console.log('report')
		}

		// skip
		else if (Sk.contains(tG)) {
			clearRater()
			// check
		}

		// submit
		else if (Sm.contains(tG)) {
			//
			storeResults()
			//
			clearRater()
			//
			checkSubmit()
			//
		}
	}

	else if (Pge===12) {
	////// /paired page
		if (IWa.contains(tG)) {
			console.log('pic a')

			if (cPair == 1) {
				IWb.className='PI'
			}

			cPair = 0
			IWa.className='PI A'
		}

		else if (IWb.contains(tG)) {
			console.log('pic b')

			if (cPair == 0) {
				IWa.className='PI'
			}

			cPair = 1
			IWb.className='PI A'
		}
	}

////// /tasks page

	// sort method in tests 
	//// NEED TO DEAL WITH THIS IN CONTEXT OF ROUTING BEHAVIOR
	else if (Pge===2) {

		if (tG === sortMethodV) {
			if (removeDropdowns(8)) {sortDropdown.className='dropsort show active A';OPN=8}
		}


		// view all regardless of task status
		else if (tflta.contains(tG) && tG !== tflta) { //a === vAll
			let aidx=key - '0'
			// make sure this is not 0 samples!
			if (cStatus!==aidx) {
				tflta.children[cStatus].className='btn'
				tflta.children[aidx].className='btn A'
				cStatus=aidx

				// refresh page
			}
		}
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

	// sign up (signupeq)
	else if (Pge==10) {
		if (signupeq.contains(tG)) {
			// check verification
			if (signupStatus == 0) {
				// go put in password or code
				// to get a seed
				//sock.send();

				// normally this is controlled elsewhere
				signupStatus = 1
			} else {
				// actually try to submit
				//sock.send()

				// if this fails
				if (1===0) {

				} else {
					rte('/')
					window.history.pushState({},'/','/')
				}
			}
		}
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












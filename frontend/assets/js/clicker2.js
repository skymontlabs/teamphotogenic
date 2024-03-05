
function parseClick()
{/*
	switch (SESSION.currentPage) {
	case PAGES.RATER:
		if (tg in BUTTONS.HOME_RATES) {
			SESSION.rating = int(key)
		}
		else if (tg in BUTTONS.HOME_TAGS) {
			SESSION.tag |= (1 << int(key))
		}
		else if (tg === BUTTONS.HOME_EXPAND) {
			DROPDOWNS.toggle(DROPDOWNS.HOME_REPORT)
		}
		else if (tg === BUTTONS.HOME_REPORT) {
			ws.reportImage()
		}
		else if (tg === BUTTONS.HOME_SKIP) {
			if (SESSION.rateQueue.length == 8) {
				ws.submitRatings()
			} else {
				SESSION.rateQueue.push([])
			}
		}
		else if (tg === BUTTONS.HOME_SUBMIT) {
			if (SESSION.rateQueue.length == 8) {
				ws.submitRatings()
			} else {
				SESSION.rateQueue.push([SESSION.rating, SESSION.tag, SESSION.comment])
			}
		}
		break;

	case PAGES.PAIRED:
		if (tg in BUTTONS.PAIRED_SELECTOR) {

		}

		else if (tg === BUTTONS.PAIRED_NEXT) {
			
		}

		else if (tg === BUTTONS.PAIRED_NEXT) {
			
		}
		break;

	case PAGES.IMAGESETS:
		if (tg === BUTTONS.IMAGESETS_DROPDOWN) {
		
		}
		break;

	case PAGES.PROFILE:
		break;
	}
*/
}

function transitionOut() {

}

function removeDropdowns()
{

}

function setRater(relem)
{
	RIm.src = relem[2]
	RBa.style.backgroundImage = `url('${relem[2]}')`

}

document.onclick = (e) =>
{
	let tg  = e.target
	let H   = tg.id
	let key = H.slice(-1)

	// possibly remove dropdown
	if (SESSION.dropdownOpen && !SESSION.dropdownOpen.contains(tg)) {
		// COPY FOR ALL DROPDOWNCLOSE
		SESSION.dropdownOpen.classList.remove('A')
		SESSION.dropdownOpen=null

// OK, WHAT IF ITS A PARENT THAT IS CLICKED ORIGINALLY, THEN CHILD, LIKE KF AND JF

		if (SESSION.dropdownOwner.contains(tg)) {
			SESSION.dropdownOwner=null
			return
		}

		SESSION.dropdownOwner=null


		// MAKE SURE THE CURRENT ONE DOES NOT OPEN THE SAME MODAL, AS IN
	}

	// possibly remove modal
	else if (SESSION.modalOpen != false) {
		if (tg === ZZ) {
			SESSION.modalOpen = false
			Ga.className=showClass[SESSION.currentPage]
		}
	}

	// link
	else if (H.slice(-1) === '_') {
		event.preventDefault();
		transitionOut()
		rte(e.target.href)
		window.history.pushState({},e.target.href,e.target.href)
		removeDropdowns()
	}





	// navigation
	if (SESSION.currentPage !== PAGES.LOGIN && Na.contains(tg)) {
		const cnameNav = {
			'Lb': [Da, Lb],
			'Pb': [Da, Lb],
			'Tb': [Da, Lb],

			'Je': [dea, Je],
			'Ke': [dea, Je],
			'Le': [dea, Je],

			'Jf': [dfa, Jf],
			'Kf': [dfa, Jf],
			'Lf': [dfa, Jf],
		}

		let cnameVal = cnameNav[tg.id]


		if (tg == Pd) {
			// this is the upload section
			Ga.className+=' showUpl';
			SESSION.modalOpen = true
		} else if (cnameVal) {
			// ALSO check to see if there is a current one
			cnameVal[0].className+=' A';
			SESSION.dropdownOpen=cnameVal[0]
			SESSION.dropdownOwner=cnameVal[1]
		}

		return
	}




	// pages
	if (SESSION.currentPage === PAGES.RATER) {
		console.log(tg)
		// fix, what if the click was outside a small box
		if (tg.id.substr(0,2) === 'Rt') {
			let aidx=key - '0'
			
			if (CONFIG.rScore!==null){Ca.children[CONFIG.rScore].className='btn BR';}
			Ca.children[aidx].className='btn BR A';
			CONFIG.rScore = aidx

			SESSION.rating = (key)
		}
		else if (BUTTONS.HOME_TAGS.contains(tg)) {
			let aidx=key.charCodeAt(0) - 97

			if (CONFIG.rTag&(1<<aidx)){Ua.children[aidx].className='BZ';CONFIG.rTag ^= (1<<aidx);}
			else{Ua.children[aidx].className='BZ A';CONFIG.rTag |= (1<<aidx);}

			SESSION.tag |= (1 << (key))
		}

		else if (Dmo.contains(tg)) {
			rMor.className+=' A';
			SESSION.dropdownOpen=rMor
			SESSION.dropdownOwner=Dmo
		}

		else if (Sk === tg || Sk.contains(tg)) {
			// BEGIN REMOVE
			if (CONFIG.rScore !== null) {
				Ca.children[CONFIG.rScore].className='btn BR';
				CONFIG.rScore = null
			}

			if (CONFIG.rTag !== 0) {
				for (let i = 0; i < 17; ++i) {
					Ua.children[i].className='BZ';
				}
				CONFIG.rTag = 0
			}

			CMa.textContent = ''
			// END REMOVE


			let toAdd = SESSION.nextQueue.shift()
			setRater(toAdd)
		}

		// bottom two are too similar, try to make code similarities and lookup tables
		else if (Sm === tg || Sm.contains(tg)) {
			console.log('submitted or skipped')

			if (CONFIG.rScore === null) {
				return
			}

			if (SESSION.nextQueue.length == 0) {
				//submitRatings(SESSION.ws, )
				console.log('destroyed')
				SESSION.rateQueue = []
				SESSION.nextQueue = SESSION.prefetchQueue
			} else {
				SESSION.rateQueue.push([CONFIG.rScore, CONFIG.tag, CONFIG.comment])
				console.log('pushed into queue')

				// this is where to divide based upon if submit or skip
				let toAdd = SESSION.nextQueue.shift()
				 console.log(toAdd)
				setRater(toAdd)
			}

			// BEGIN REMOVE
			Ca.children[CONFIG.rScore].className='btn BR';
			CONFIG.rScore = null

			for (let i = 0; i < 17; ++i) {
				Ua.children[i].className='BZ';
			}
			CONFIG.rTag = 0
			CMa.textContent = ''
			// END REMOVE


			if (SESSION.nextQueue.length == 1) {
				// prefetch
				//SEND_WS_PREFETCH_RATINGS()
			}
		}
	}

	// paired
	else if (SESSION.currentPage === PAGES.PAIRED) {
		if (IWa.contains(tg)) {
			CONFIG.pSel = 0
		}

		else if (IWb.contains(tg)) {
			CONFIG.pSel = 1
		}

		else if (tg === BUTTONS.PAIRED_SKIP) {
			if (SESSION.nextQueue.length == 0) {
				SESSION.rateQueue = []
				SESSION.nextQueue = SESSION.prefetchQueue
			} else {
				SESSION.rateQueue.push([tg === BUTTONS.HOME_SUBMIT, CONFIG.pairing, CONFIG.pSel])

				// this is where to divide based upon if submit or skip
				let toAdd = SESSION.nextQueue.shift()
				setRater(toAdd)
			}

			if (SESSION.nextQueue.length == 1) {
				// prefetch
				//SEND_WS_PREFETCH_RATINGS()
			}
		}

		else if (tg === BUTTONS.PAIRED_NEXT) {
			// remove coloring CONFIG.pSel
			CONFIG.pSel = null
			
		}
	}

	else if (SESSION.currentPage === PAGES.IMAGESETS) {
		const imsTypeFilter = {
			'Bv0': [7,0],
			'Bw0': [7,0],
			'Bv1': [1,1],
			'Bw1': [1,1],
			'Bv2': [2,2],
			'Bw2': [2,2],
			'Bv3': [4,3],
			'Bw3': [4,3],
		};


		let sortElems = [Bv0, Bv1, Bv2, Bv3]
		let flt = imsTypeFilter[tg.id]

		if (flt) {
			CONFIG.iFilter ^= flt

 			if (CONFIG.iFilter == 0) {
				// set all to be the case
				CONFIG.iFilter = 7
			}

			if (CONFIG.iFilter == 7) {
				// 
				Bv0.className = 'btn A'
				for (let i = 1; i < 4; ++i) {
					sortElems[i].className = 'btn'
				}
			} else {
				for (let i = 0; i < 4; ++i) {
					if (CONFIG.iFilter & (1 << i)) {
						sortElems[i].className = 'btn A'
					} else {
						sortElems[i].className = 'btn'
					}
				}
			}
		}

		// dropdown sort open
		// OK, SO THIS SHOULD NOT OPEN AGAIN IF IT WAS PREVIOUSLY OPEN

		else if (sortMethodV.contains(tg)) {
			sortDropdown.className+=' A';
			SESSION.dropdownOpen=sortDropdown
			SESSION.dropdownOwner=sortMethodV
		}

		// dropdown values
		else if (sortDropdown.contains(tg) && tg != sortDropdown) {
			alert(key)
			CONFIG.iFilter = key

			sortMethodV.textContent = IMAGESET_SORT_FUNCTIONS[key]

			tg.className+=' active'
			//.classList.remove('active')

			SESSION.dropdownOpen.classList.remove('A')
			SESSION.dropdownOpen=null
		}

		// individual test dropdown open
		else if (TLS.contains(tg) && (tg.parentNode.id.charAt(0)=='Y'||tg.id.charAt(0)=='Y')) {
			//
			let idv = (tg.id !== '') ? tg.id : tg.parentNode.id
			let dmenu = CTRLV.iDropdownLUT[idv]
			dmenu.className+=' A'
			SESSION.dropdownOpen=dmenu
			SESSION.dropdownOwner=tg
		}

		// delete test
		else if (tg.id.charAt(0)=='Q') {
			tg.parentNode.classList.remove('A')

			SESSION.dropdownOpen=null
			SESSION.dropdownOwner=null
		}

		// pause test
		else if (tg.id.charAt(0)=='K') {
			tg.parentNode.classList.remove('A')
		}

		// resume test
		else if (tg.id.charAt(0)=='J') {
			tg.parentNode.classList.remove('A')
		}
		
	}

	else if (SESSION.currentPage === PAGES.LOGIN) {
		// login
		if (signupeq.contains(tg)) {

			if (CTRLV.signupStatus == 0) {
				// go put in password or code
				// to get a seed
				//sock.send();

				// normally this is controlled elsewhere
				CTRLV.signupStatus = 1

				genPhrase2()
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

	else if (SESSION.currentPage === PAGES.SIGNUP) {

	}

	else if (SESSION.currentPage === PAGES.PROFILE) {

	}

	// profile subpage
	else if (SESSION.currentPage === PAGES.PROFILE) {

	}

	// profile subpage
	else if (SESSION.currentPage === PAGES.PROFILE) {

	}

	else {

	}

	//
};


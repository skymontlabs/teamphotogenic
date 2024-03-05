function cleared() {
}

const authFunctions = [
    getRater,
    getRater,
    getPaired,
    getAllTests,
    getTestID,
    getImageID,
    getPrf,
    /*
    getSecurity,
    getAlerts,
    getBilling,
    getStatistics,
    getPremium,*/
]

const nonAuthFunctions = [
    genLogin,
    /*
    getSignup,
    getForgotPassword,
    getResetPassword,*/
]


function rte(url) {
	let pg = url.split('/').pop()
	if (SESSION.currentPageStr === pg) {return}

	// path name
	let pid = pathnames[pg]
	SESSION.currentPageStr = pg

	const params = new Proxy(new URLSearchParams(window.location.search),
	{
	  get: (searchParams, prop) => searchParams.get(prop),
	});

	console.log(pg)
	// CURRENT FUCKING PAGE


	if (SESSION.loggedIn === false) {
		if (pid<12) {
			
		}
		clearMn(Mn)
		nonAuthFunctions[pid - 12]()
	} else {
		clearMn(Mn)
		console.log(authFunctions[pid])
		console.log(pid)
		authFunctions[pid]()
	}

	Ga.className = showClass[pid]
	SESSION.currentPage = pid
}

/*
else if (pg === '') {
		SESSION.currentPage = PAGES.RATER

		//Ga.className = 'showRate';
		clearMn(Mn)
		getRater()
	} else if (pg === 'paired') {
		SESSION.currentPage = PAGES.PAIRED
		clearMn(Mn)
	

		//Ga.className = 'showPaired';
		clearMn(Mn)
		getRater()
	} else if (pg === 'imagesets') {
		SESSION.currentPage = PAGES.IMAGESETS
		
		clearMn(Mn, true)
		//Ga.className = 'showTasks';
		
		let limit = params.limit
		let offset = params.offset
		
		// in real life do callback mode...
		getAllTests()
	} else if (pg === 'imagesetid') {
		SESSION.currentPage = PAGES.IMAGESET_ID
		clearMn(Mn)
		
		//Ga.className = 'showTaskID';
		getTestID(params.iid)
	} else if (pg === 'imageID') {
		SESSION.currentPage = PAGES.IMAGE_ID
		clearMn(Mn)
		
		//Ga.className = 'showTasks showImg';
		generateImage(params.iid);
	} else if (pg === 'profile') {
		SESSION.currentPage = PAGES.PROFILE
		clearMn(Mn)
		
		genPrf()
		//Ga.className = 'showProfile edit';
	} else if (pg === 'security') {
		SESSION.currentPage = PAGES.PROFILE_SECURITY
		clearMn(Mn)
		
		//Ga.className = 'showProfile sec';
	} else if (pg === 'alerts') {
		SESSION.currentPage = PAGES.PROFILE_ALERTS
		clearMn(Mn)
		
		//Ga.className = 'showProfile alr';
	} else if (pg === 'billing') {
		SESSION.currentPage = PAGES.PROFILE_BILLING
		clearMn(Mn)
		
		//Ga.className = 'showProfile bil';
	} else if (pg === 'help') {
		SESSION.currentPage = PAGES.PROFILE_BILLING
		clearMn(Mn)
		
		//Ga.className = 'showProfile hlp';
	} else if (pg === 'statistics') {
		SESSION.currentPage = PAGES.STATISTICS
		clearMn(Mn)
		
		//Ga.className = 'showTaskID';
		let iid = 1
	} else if (pg === 'notifications') {
		SESSION.currentPage = PAGES.NOTIFICATIONS
		clearMn(Mn)
		
		//Ga.className = 'showNotifications';
	} else if (pg === 'premium') {
		SESSION.currentPage = PAGES.PREMIUM
		clearMn(Mn)
		
		//Ga.className = 'showPremium';
	} else if (pg === 'r2') {
		SESSION.currentPage = PAGES.STATISTICS
		//Ga.className = 'showR2';
	} else {
		alert('phucc')
	}
	*/

function pth() {
	rte(window.location.pathname)
	window.history.pushState({},window.location.pathname,window.location.pathname)
}

pth()


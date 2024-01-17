const DIV = document.createElement('div')

const DIX = DIV.cloneNode(true)
const DII = DIV.cloneNode(true)
DII.className='x'
DIX.appendChild(DII)

const DYZ = DIV.cloneNode(true)
DYZ.className='y z'
const SPN = document.createElement('span')
const BTN = document.createElement('button')
const INP = document.createElement('input')
const H2 = document.createElement('h2')
const H4 = document.createElement('h4')
const AX = document.createElement('a')
const UL = document.createElement('ul')
const LI = document.createElement('li')


//https://measurethat.net/Benchmarks/Show/10210/0/remove-all-children-from-dom-element
function clearMn(nde, cleanChild=false) {
	//console.log(nde, cleanChild)
	while (nde.lastElementChild && nde.lastElementChild.className.substr(0,1) != 'x') {
		console.log(nde.lastElementChild)
	    nde.removeChild(nde.lastElementChild);
	}

	let Xo = nde.firstElementChild
	//console.log(Xo)
	if (Xo.hasChildNodes()) {
		while (Xo.lastElementChild) {
		    Xo.removeChild(Xo.lastElementChild);
		}
	}

	if (nde.firstElementChild.className != 'x' && cleanChild) {
		nde.firstElementChild.className = 'x'
	}
}


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

function cr8_dt() {
  let DT = BTN.cloneNode(true)
  DT.className = 'dots btn L16'
  let D0 = SPN.cloneNode(true)
  D0.className = 'd0'
  let D1 = SPN.cloneNode(true)
  D1.className = 'd1'
  let D2 = SPN.cloneNode(true)
  D2.className = 'd2'

  DT.appendChild(D0)
  DT.appendChild(D1)
  DT.appendChild(D2)

  return DT
}

// hamburger
let HMB = cr8_dt()


let Mn = DIV.cloneNode(true)
Mn.id = 'Mn'
let xblk = DIV.cloneNode(true)
xblk.className='x'

Mn.appendChild(xblk)
Ga.appendChild(Mn)


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



function cleared() {
	
}
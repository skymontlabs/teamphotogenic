const DIV = document.createElement('div')
const SPN = document.createElement('span')
const BTN = document.createElement('button')
const INP = document.createElement('input')
const H4 = document.createElement('h4')
const AX = document.createElement('a')

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

let DZ = cr8_dt()

/*

<button id="dropdownDotsg" class="dots btn border"><span class="dlef" id="dd0X"></span>
<span class="dmid" id="dd1X"></span><span class="drig" id="dd2X"></span></button>



  const tagWrap = DIV.cloneNode(true)
  for (var i = 0; i < 6; ++i) {
    const tagElem = score.cloneNode(true)
    tagElem.className='btn-tag'
  }*/

  /*
          <div class="taskItem">
            <div class="y z">
              <h6>Laurie in Italy69420</h6>
              <time>3y</time>
            </div>
            <div class="imgWrap">
              <img class="imgMat" src="img/laurie.jpg" alt="">
              <img class="imgMat" src="img/laurie.jpg" alt="">
              <img class="imgMat" src="img/laurie.jpg" alt="">
              <img class="imgMat" src="img/laurie.jpg" alt="">
              <img class="imgMat" src="img/laurie.jpg" alt="">
              <img class="imgMat" src="img/laurie.jpg" alt="">
            </div>
            <div class="mtaWrap y z">
              <span class="data-score">7.49</span>
              <div style="margin-left:auto;">
                <span class="btn-datapoint">🌄 13 images</span>
                <span class="btn-datapoint">🏷️ 13 tags</span>
                <span class="btn-datapoint">💬 13 comments</span>
              </div>
            </div>
          </div>*/

/**/

function taskData() {
  const taskItem = DIV.cloneNode(true)
  taskItem.className = 'taskItem'

  const imgWrap = DIV.cloneNode(true)
  imgWrap.className = 'imgWrp'
  const imgMat = AX.cloneNode(true)
  imgMat.style.background = 'url("img/laurie.jpg")'
  imgMat.style.backgroundSize = 'cover'
  imgMat.href = '/imageID'
  for (var i = 0; i < 3; ++i) {
    const imgClone = imgMat.cloneNode(true)
    imgClone.style.height = '130px'
    imgWrap.appendChild(imgClone)
  }
  imgMat.id = 'fillImg'


  const txtWrap = DIV.cloneNode(true)
  txtWrap.className = 'y'
  const title = document.createElement('h6')
  title.innerText = 'seggs'
  const imgCt = SPN.cloneNode(true)
  imgCt.className = 'dtpt'
  imgCt.innerText = '13 images'
  const time = document.createElement('time')
  time.innerText = '5y'
  const dtv = DZ.cloneNode(true)

  //<button id="dropdownDotsX" class="dots btn border"><span class="dlef" id="dd0X"></span><span class="dmid" id="dd1X"></span><span class="drig" id="dd2X"></span></button>


  txtWrap.appendChild(title)
  txtWrap.appendChild(imgCt)
  txtWrap.appendChild(time)
  txtWrap.appendChild(dtv)


  taskItem.appendChild(imgMat)
  taskItem.appendChild(imgWrap)
  taskItem.appendChild(txtWrap)

  TLS.appendChild(taskItem)
}

function filterStatus() {
  /*
  <div id="tflta">
    <button id="Bv0" class="btn A">
      <span id="Bw0" class="F12 ST">All</span>
      <h4 id="Bx0">12</h4>
    </button>
    <button id="Bv1" class="btn">
      <span id="Bw1" class="F12 ST">Running</span>
      <h4 id="Bx1">1</h4>
    </button>
    <button id="Bv2" class="btn">
      <span id="Bw2" class="F12 ST">Paused</span>
      <h4 id="Bx2">0</h4>
    </button>
    <button id="Bv3" class="btn">
      <span id="Bw3" class="F12 ST">Finished</span>
      <h4 id="Bx3">11</h4>
    </button>
  </div>
  */
  let Pr = DIV.cloneNode(true)
  let Bn = BTN.cloneNode(true)
  let Sx = SPN.cloneNode(true)
  let Zx = H4.cloneNode(true)
  Bn.id='Bv0'
  Bn.className='btn A'
  Sx.id='Bw0'
  Sx.className='F12 ST'
  Zx.id='Bx0'
  Bn.appendChild(Sx)
  Bn.appendChild(Zx)
  let b1 = Bn.cloneNode(true)
  let b2 = Bn.cloneNode(true)
  let b3 = Bn.cloneNode(true)

  Pr.appendChild(bn)
  Pr.appendChild(b1)
  Pr.appendChild(b2)
  Pr.appendChild(b3)
  return Pr
}


function imageIndiv() {
  const imgItem = DIV.cloneNode(true)
  imgItem.className = 'taskItem rel'

  const imgWrap = AX.cloneNode(true)
  imgWrap.className = ''
  imgWrap.href = '/imageID'
  const imgMat = document.createElement('img')
  imgMat.src = 'img/laurie.jpg'
  imgMat.alt = 'Sample image'
  imgWrap.appendChild(imgMat)


  const mtaWrap = DIV.cloneNode(true)
  mtaWrap.className = 'W D imgData abs y z'

  const score = document.createElement('span')
  
  const ctWrap = DIV.cloneNode(true)
  const comCt = score.cloneNode(true)
  comCt.className = 'acomm'
  score.className = 'ascore'
  score.innerText = '5.69'
  ctWrap.className = 'mla'
  comCt.innerText = '13 comments'

  ctWrap.appendChild(comCt)
  mtaWrap.appendChild(score)
  mtaWrap.appendChild(ctWrap)

  imgItem.appendChild(imgWrap)
  imgItem.appendChild(mtaWrap)

  TLS.appendChild(imgItem)
}


function imageModal() {

}



function imageModal() {

}




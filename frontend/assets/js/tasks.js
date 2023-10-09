
function setupMeters() {
  numTask.innerText = '30'
  numImg.innerText = '30'
  numCom.innerText = '30'
  curCre.innerText = '30'
}

const DIV = document.createElement('div')
const SPN = document.createElement('span')
const BTN = document.createElement('button')
const AX = document.createElement('a')


/*
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
function taskData2() {

}

function taskData2() {
  const taskItem = DIV.cloneNode(true)
  taskItem.className = 'taskItem'

  const imgWrap = DIV.cloneNode(true)
  imgWrap.className = 'imgWrap'
  const imgMat = document.createElement('img')
  for (var i = 0; i < 6; ++i) {
    const imgClone = imgMat.cloneNode(true)
    imgClone.src = 'img/laurie.jpg'
    imgClone.alt = 'Sample image'
    imgWrap.appendChild(imgClone)
  }

  const txtWrap = DIV.cloneNode(true)
  txtWrap.className = 'y z'
  const title = document.createElement('h6')
  title.innerText = 'seggs'
  const time = document.createElement('time')
  time.innerText = '5y'
  txtWrap.appendChild(title)
  txtWrap.appendChild(time)

  const mtaWrap = DIV.cloneNode(true)
  mtaWrap.className = 'mtaWrap y z'

  const score = document.createElement('span')
  
  const ctWrap = DIV.cloneNode(true)
  const imgCt = score.cloneNode(true)
  const comCt = score.cloneNode(true)
  imgCt.className = 'btn-datapoint'
  comCt.className = 'btn-datapoint'

  score.className = 'data-score'
  score.innerText = '5.69'
  ctWrap.className = 'mla'
  imgCt.innerText = '🌄 13 images'
  comCt.innerText = '💬 13 comments'

  ctWrap.appendChild(imgCt)
  ctWrap.appendChild(comCt)
  mtaWrap.appendChild(score)
  mtaWrap.appendChild(ctWrap)

  taskItem.appendChild(imgWrap)
  taskItem.appendChild(txtWrap)
  taskItem.appendChild(mtaWrap)

  tasklist.appendChild(taskItem)
}


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
  const time = document.createElement('time')
  time.innerText = '5y'

  const mtaWrap = DIV.cloneNode(true)
  mtaWrap.className = 'mtaWrap y z'

  
  const ctWrap = SPN.cloneNode(true)
  const imgCt = SPN.cloneNode(true)
  imgCt.className = 'btn-datapoint'

  imgCt.innerText = '13 images'

  //<button id="dropdownDotsX" class="dots btn border"><span class="dlef" id="dd0X"></span><span class="dmid" id="dd1X"></span><span class="drig" id="dd2X"></span></button>


  txtWrap.appendChild(title)
  txtWrap.appendChild(imgCt)
  txtWrap.appendChild(time)


  taskItem.appendChild(imgMat)
  taskItem.appendChild(imgWrap)
  taskItem.appendChild(txtWrap)

  tasklist.appendChild(taskItem)
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
  mtaWrap.className = 'mtaWrap imgData abs y z'

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

  tasklist.appendChild(imgItem)
}

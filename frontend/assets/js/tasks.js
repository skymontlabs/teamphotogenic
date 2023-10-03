
function setupMeters() {
  numTask.innerText = '30'
  numImg.innerText = '30'
  numCom.innerText = '30'
  curCre.innerText = '30'
}



function taskData() {
  const taskItem = document.createElement('div')
  taskItem.className = 'taskItem'

  const txtWrap = document.createElement('div')
  txtWrap.className = 'y z'
  const title = document.createElement('h6')
  title.innerText = 'seggs'
  const time = document.createElement('time')
  time.innerText = '5y'
  txtWrap.appendChild(title)
  txtWrap.appendChild(time)

  const imgWrap = document.createElement('div')
  imgWrap.className = 'imgWrap'
  const imgMat = document.createElement('img')
  for (var i = 0; i < 6; ++i) {
    const imgClone = imgMat.cloneNode(true)
    imgClone.src = 'img/laurie.jpg'
    imgClone.alt = 'Sample image'
    imgWrap.appendChild(imgClone)
  }

  const mtaWrap = document.createElement('div')
  mtaWrap.className = 'mtaWrap y z'

  const score = document.createElement('span')
  
  const ctWrap = document.createElement('div')
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

  taskItem.appendChild(txtWrap)
  taskItem.appendChild(imgWrap)
  taskItem.appendChild(mtaWrap)

  tasklist.appendChild(taskItem)

/*
  const tagWrap = document.createElement('div')
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
}

taskData()

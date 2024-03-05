function filterStatus() {
  let Bn = BTN.cloneNode(true)
  Bn.id='Bv0'
  Bn.className='btn'

  let Sx = SPN.cloneNode(true)
  Sx.id='Bw0'
  Sx.className='F12 ST'
  Sx.textContent='All'

  let Zx = H4.cloneNode(true)
  Zx.id='Bx0'
  Zx.textContent='14'
  Bn.appendChild(Sx)
  Bn.appendChild(Zx)

  let b1 = Bn.cloneNode(true)
  b1.id='Bv1'
  b1.children[0].id='Bw1'
  b1.children[0].textContent='Running'
  b1.children[1].id='Bx1'
  b1.children[1].textContent='1'
  let b2 = Bn.cloneNode(true)
  b2.id='Bv2'
  b2.children[0].id='Bw2'
  b2.children[0].textContent='Paused'
  b2.children[1].id='Bx2'
  b2.children[1].textContent='12'
  let b3 = Bn.cloneNode(true)
  b3.id='Bv3'
  b3.children[0].id='Bw3'
  b3.children[0].textContent='Finished'
  b3.children[1].id='Bx3'
  b3.children[1].textContent='1'
  Bn.className='btn A'


  let Pr = DIV.cloneNode(true)
  Pr.id='tflta'
  Pr.appendChild(Bn)
  Pr.appendChild(b1)
  Pr.appendChild(b2)
  Pr.appendChild(b3)

  //Ta.children[0].appendChild(Pr)
  return Pr
}

function getTimeDistanceToTodayOptimized(unixTimestamp) {
    const givenDate = new Date(unixTimestamp * 1000);
    const today = new Date();

    // Calculate the total difference in days first (most likely scenario)
    const differenceInDays = Math.floor((today - givenDate) / (86400000));

    if (differenceInDays >= 365) {
        const years = Math.floor(differenceInDays / 365);
        return `${years}y`;
    } else if (differenceInDays >= 30) {
        const months = Math.floor(differenceInDays / 30); // A rough approximation
        return `${months}m`;
    } else if (differenceInDays >= 1) {
        return `${differenceInDays}d`;
    } else {
        // If less than a day, calculate hours, then minutes, then seconds
        const differenceInHours = Math.floor((today - givenDate) / (3600000));
        if (differenceInHours >= 1) {
            return `${differenceInHours}h`;
        } else {
            const differenceInMinutes = Math.floor((today - givenDate) / (60000));
            if (differenceInMinutes >= 1) {
                return `${differenceInMinutes}min`;
            } else {
                const differenceInSeconds = Math.floor((today - givenDate) / 1000);
                return `${differenceInSeconds}sec`;
            }
        }
    }
}



function taskData(id, title, imgs, age)
{
  const taskItem = DIV.cloneNode(true)
  taskItem.className = 'taskItem'

  const imgWrap = DIV.cloneNode(true)
  imgWrap.className = 'imgWrp'
  const imgMat = AX.cloneNode(true)
  imgMat.style.backgroundImage = `url("img/${imgs[0]}")`
  imgMat.style.backgroundSize = 'cover'
  imgMat.href = '/imageID'
  for (var i = 1; i < 4; ++i) {
    const imgClone = imgMat.cloneNode(true)
    imgClone.style.backgroundImage = `url("img/${imgs[i]}")`
    imgClone.style.height = '130px'
    imgWrap.appendChild(imgClone)
  }
  imgMat.className = 'fillImg'

  const txtWrap = DIV.cloneNode(true)
  txtWrap.className = 'y rel'
  const tdv = document.createElement('h6')
  tdv.textContent = title
  const imgCt = SPN.cloneNode(true)
  imgCt.className = 'dtpt'
  imgCt.textContent = '13 images'
  const time = document.createElement('time')
  time.textContent = getTimeDistanceToTodayOptimized(age)
  const dtv = HMB.cloneNode(true)
  dtv.id = 'Y'+ id

  let mod = getDropdownMini('Z'+ id,['Delete','Pause','Resume'],3,['Q','K','J'],'U')
  CTRLV.iDropdownLUT['Y'+ id] = mod
  console.log(mod)


  txtWrap.appendChild(tdv)
  txtWrap.appendChild(imgCt)
  txtWrap.appendChild(time)
  txtWrap.appendChild(dtv)
  txtWrap.appendChild(mod)


  taskItem.appendChild(imgMat)
  taskItem.appendChild(imgWrap)
  taskItem.appendChild(txtWrap)

  return taskItem
}


function dropdownValue(ulid,chld,chldct,acv,baseval) {
  /*
  <ul id="sortDropdown" class="dropsort show active A">
    <li id="Sd0" class="noselect active">Average score</li>
    <li id="Sd1" class="noselect">Median score</li>
    <li id="Sd2" class="noselect">Date created</li>
    <li id="Sd3" class="noselect">Date created</li>
  </ul>

  <div class="dropdownSelector">
    <span id="sortMethodV" class="selClick crt">Average score</span>
    <ul id="sortDropdown" class="dropsort">
      <li id="Sd0" class="noselect active">Average score</li>
      <li id="Sd1" class="noselect">Median score</li>
      <li id="Sd2" class="noselect">Date created</li>
      <li id="Sd3" class="noselect">Date created</li>
    </ul>
  </div>
  */

  let DS=DIV.cloneNode(true)
  DS.className='dropdownSelector'
  
  let SM=SPN.cloneNode(true)
  SM.id='sortMethodV'
  SM.className='selClick crt'
  SM.textContent=chld[acv]

  let U=UL.cloneNode(true)
  U.id=ulid
  U.className='dropsort'
  for (var i = 0; i < chldct; i+=1) {
    let L=LI.cloneNode(true)
    L.id = 'Sd' + String.fromCharCode(baseval + i)
    L.className = 'noselect'
    L.textContent=chld[i]
    U.appendChild(L)
  }
  U.children[acv].className='noselect active'

  SM.textContent=chld[acv]

  DS.appendChild(SM)
  DS.appendChild(U)

  return DS
}

function getTestNav()
{
  var TsT=H2.cloneNode(true)
  TsT.id='Fa'
  TsT.textContent='Tests'

  var testnav=DIV.cloneNode(true) 
  testnav.className='wrapsort y z rel BB'

  testnav.appendChild(TsT)
  testnav.appendChild(dropdownValue('sortDropdown',IMAGESET_SORT_FUNCTIONS,3,0,48))

  return testnav
}

function getAllImagesets(imagesetCt)
{
  Mn.id='Ta'

  Mn.children[0].appendChild(getTestNav())
  Mn.children[0].appendChild(filterStatus())
  
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'

  let ict = DATAV.iImagesetList.length
  for (let i = 0; i < ict; ++i) {
    let ims = DATAV.iImagesetList[i]
    Tls.appendChild(taskData(ims[0], ims[2], ims[1], ims[4]))
  }

  Mn.children[0].appendChild(Tls)
}












function getAllTests() {
  getAllImagesets(1)
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

  const score = SPN.cloneNode(true)
  
  const ctWrap = DIV.cloneNode(true)
  const comCt = score.cloneNode(true)
  comCt.className = 'acomm'
  score.className = 'ascore'
  score.textContent = '5.69'
  ctWrap.className = 'mla'
  comCt.textContent = '13 votes'

  ctWrap.appendChild(comCt)
  mtaWrap.appendChild(score)
  mtaWrap.appendChild(ctWrap)

  imgItem.appendChild(imgWrap)
  imgItem.appendChild(mtaWrap)

  return imgItem
}


function getPaired() {
  /*
  <div id="Xa" class="">
    <div class="x">
      <div id="RSa">
        <div id="IWa" class="PI">
          <img id="IMa" src="img/laurie.jpg">
        </div>
        <div id="IWb" class="PI">
          <img id="IMb" src="img/lake.jpg">
        </div>
      </div>
    </div>
  </div>
  */
  // Create the outermost div
  //let divXa=DIV.cloneNode(true);
  Mn.id='Xa';

  // Create the child div with class 'x'
  let divX=Mn.children[0]

  // Create the div with id 'RSa'
  let divRSa=DIV.cloneNode(true)
  divRSa.id='RSa';

  // Create the first inner div with id 'IWa' and class 'PI'
  let divIWa=DIV.cloneNode(true)
  divIWa.id='IWa';
  divIWa.className='PI';

  // Create the img inside 'IWa'
  let imgIMa=document.createElement('img');
  imgIMa.id='IMa';
  imgIMa.src='img/laurie.jpg';

  // Append imgIMa to divIWa
  divIWa.appendChild(imgIMa);

  // Create the second inner div with id 'IWb' and class 'PI'
  let divIWb = DIV.cloneNode(true)
  divIWb.id = 'IWb';
  divIWb.className = 'PI';

  // Create the img inside 'IWb'
  let imgIMb = document.createElement('img');
  imgIMb.id = 'IMb';
  imgIMb.src = 'img/lake.jpg';

  // Append imgIMb to divIWb
  divIWb.appendChild(imgIMb);

  // Append divIWa and divIWb to divRSa
  divRSa.appendChild(divIWa);
  divRSa.appendChild(divIWb);

  // Append divRSa to divX
  divX.appendChild(divRSa);

}



function getTestID() {
  Mn.id='Ta';
  Mn.className='oh';

  Mn.children[0].appendChild(testidmta())
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'
  Tls.appendChild(imageIndiv())
  Mn.children[0].appendChild(Tls)

}





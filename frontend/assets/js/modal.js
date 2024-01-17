function gTFA()
{
  // Create the main div
  const panel2aDiv = DIV.cloneNode(true)
  panel2aDiv.id = 'panel2a';
  panel2aDiv.classList.add('dn');

  // Add the paragraphs
  const p1 = document.createElement('p');
  p1.textContent = 'Scan this QR code and copy down this';
  panel2aDiv.appendChild(p1);

  const p2 = document.createElement('p');
  p2.textContent = 'If you lose this secret, you will need to contact support and pass more sophisticated authentication to regain access to your account.';
  panel2aDiv.appendChild(p2);

  // Create and append the SVG
  const svg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
  svg.setAttribute('id', 'QRa');
  svg.setAttribute('xmlns', 'http://www.w3.org/2000/svg');
  svg.setAttribute('xml:space', 'preserve');
  svg.setAttribute('viewBox', '0 0 33 33');
  svg.setAttribute('style', 'width: 330px;');

  const rects = [
    { x: '0.5', y: '0.5', width: '6', height: '6', fill: 'white', strokeWidth: '1', stroke: 'black', strokeAlign: 'outer' },
    { x: '2', y: '2', width: '3', height: '3' },
    { x: '26.5', y: '0.5', width: '6', height: '6', fill: 'white', strokeWidth: '1', stroke: 'black', strokeAlign: 'outer' },
    { x: '28', y: '2', width: '3', height: '3' },
    { x: '0.5', y: '26.5', width: '6', height: '6', fill: 'white', strokeWidth: '1', stroke: 'black', strokeAlign: 'outer' },
    { x: '2', y: '28', width: '3', height: '3' },
    { x: '26', y: '26', width: '7', height: '7' }
  ];

  rects.forEach(rectData => {
    const rect = document.createElementNS('http://www.w3.org/2000/svg', 'rect');
    for (let attr in rectData) {
        rect.setAttribute(attr, rectData[attr]);
    }
    svg.appendChild(rect);
  });

  panel2aDiv.appendChild(svg);

  // Add the button
  const button = document.createElement('button');
  button.textContent = 'Next';
  panel2aDiv.appendChild(button);

  // Return the main div
  return panel2aDiv;
}

function generateBuyCredDataDiv() {
    const buyCredDataDiv = DIV.cloneNode(true)
    buyCredDataDiv.id = 'buyCredData';
    buyCredDataDiv.className = 'box-layout abs';
    buyCredDataDiv.style.display = 'none';

    const creditData = [
        { id: 'z40c', price: '$5', quantity: '50 Credits', discount: null },
        { id: 'z100c', price: '$9', quantity: '100 Credits', discount: '10% discount' },
        { id: 'z250c', price: '$13', quantity: '150 Credits', discount: '13% discount' },
        { id: 'z500c', price: '$16', quantity: '200 Credits', discount: '20% discount' }
    ];

    creditData.forEach(data => {
        const div = DIV.cloneNode(true)
        div.id = data.id;
        div.className = 'mt11 pt11 buy-button';

        const creditBuyDiv = DIV.cloneNode(true)
        creditBuyDiv.className = 'credit-buy';

        const a = document.createElement('a');
        a.href = '/';
        a.target = '_blank';
        a.className = 'w48p price v mat buy w5 tr btn-primary f17';
        const span = document.createElement('span');
        span.textContent = data.price;
        a.appendChild(span);
        creditBuyDiv.appendChild(a);

        const quantityDiv = DIV.cloneNode(true)
        quantityDiv.className = 'quantity v w120p w6';
        quantityDiv.textContent = data.quantity;
        creditBuyDiv.appendChild(quantityDiv);

        if (data.discount) {
            const discDiv = DIV.cloneNode(true)
            discDiv.className = 'disc';
            discDiv.textContent = data.discount;
            creditBuyDiv.appendChild(discDiv);
        }

        div.appendChild(creditBuyDiv);
        buyCredDataDiv.appendChild(div);
    });

    const dnDiv = DIV.cloneNode(true)
    dnDiv.className = 'dn';

    const h2 = document.createElement('h2');
    h2.textContent = 'Checkout';
    dnDiv.appendChild(h2);

    const inputWrapper = DIV.cloneNode(true)
    ['CCcodea', 'CCexpa', 'CCcvva'].forEach((id, index) => {
        const input = document.createElement('input');
        input.id = id;
        input.type = index === 2 ? 'number' : 'text';
        inputWrapper.appendChild(input);
    });

    dnDiv.appendChild(inputWrapper);
    buyCredDataDiv.appendChild(dnDiv);

    return buyCredDataDiv;
}



function gReport() {
    // Create the main div
    const repaDiv = DIV.cloneNode(true)
    repaDiv.className = 'abs dn';
    repaDiv.style.background = 'white';
    repaDiv.style.width = '700px';
    repaDiv.style.display = 'none';
    repaDiv.id = 'REPa';

    // Add the header
    const h3 = document.createElement('h3');
    h3.textContent = 'Are you sure you want to report this image?';
    repaDiv.appendChild(h3);

    // Add the paragraph
    const p = document.createElement('p');
    p.textContent = 'Images can be reported for being spammy, pornographic, or harassing.';
    repaDiv.appendChild(p);

    // Add the button
    const button = document.createElement('button');
    button.className = 'btn alt';
    button.textContent = 'Submit';
    repaDiv.appendChild(button);

    // Return the main div
    return repaDiv;
}

function createDropAreaDiv() {
    const dropAreaDiv = DIV.cloneNode(true)
    dropAreaDiv.id = 'dropArea';
    dropAreaDiv.classList.add('y', 'z');

    const innerDiv1 = DIV.cloneNode(true)
    innerDiv1.style.width = '500px';

    const form = document.createElement('form');
    form.classList.add('my-form');

    const ptxt = document.createElement('p');
    ptxt.id = 'ptxt';
    ptxt.textContent = 'Upload multiple files with the file dialog or by dragging and dropping images onto the dashed region';
    form.appendChild(ptxt);

    const fileInput = document.createElement('input');
    fileInput.type = 'file';
    fileInput.id = 'fileElem';
    fileInput.multiple = true;
    fileInput.accept = 'image/*';
    fileInput.setAttribute('onchange', 'handleFiles(this.files)');
    form.appendChild(fileInput);

    const label = document.createElement('label');
    label.id = 'UpB';
    label.classList.add('button');
    label.setAttribute('for', 'fileElem');
    label.textContent = 'Select some files';
    form.appendChild(label);

    innerDiv1.appendChild(form);

    const instructionP = document.createElement('p');
    instructionP.classList.add('dn');
    instructionP.textContent = 'Implement a dropdown function for the gallery that would include a caret. This is so we can hide the images if the user believes it to be annoying. Also allow for deletion and addition of images. No make this a gallery like instagram, but where you can go through a total filelevel view';
    innerDiv1.appendChild(instructionP);

    const img = document.createElement('img');
    img.id = 'prvIm';
    img.style.width = '500px';
    innerDiv1.appendChild(img);

    const upgalDiv = DIV.cloneNode(true)
    upgalDiv.id = 'upgal';
    upgalDiv.classList.add('GaL', 'y');
    innerDiv1.appendChild(upgalDiv);

    dropAreaDiv.appendChild(innerDiv1);

    // Task preferences
    const updDiv = DIV.cloneNode(true)
    updDiv.id = 'Upd';
    updDiv.classList.add('dn');
    updDiv.style.width = '400px';
    updDiv.style.padding = '0 24px';
    updDiv.style.boxSizing = 'border-box';

    const h4 = document.createElement('h4');
    h4.style.margin = '0';
    h4.style.padding = '24px 0 12px';
    h4.textContent = 'Task preferences';
    updDiv.appendChild(h4);

    // Age section
    const ageSection = cre8slider('Age', 'scoreRangex', 10, 40, null, null);
    updDiv.appendChild(ageSection);

    // Gender section
    const genderDiv = createGenderSection();
    updDiv.appendChild(genderDiv);

    // Votes per image section
    const votesSection = cre8slider('# votes / image', 'scoreRang', 25, null, 1, 10000);
    updDiv.appendChild(votesSection);

    const creditSpan1 = document.createElement('span');
    creditSpan1.classList.add('F12', 'T16');
    creditSpan1.textContent = 'Credits needed';
    updDiv.appendChild(creditSpan1);

    updDiv.appendChild(document.createElement('br'));

    const creditSpan2 = document.createElement('span');
    creditSpan2.textContent = '10 images x 10 votes/image = 100 credits';
    updDiv.appendChild(creditSpan2);

    const submitButton = document.createElement('button');
    submitButton.style.width = '100%';
    submitButton.style.margin = '2em 0 0';
    submitButton.classList.add('btn', 'blue');
    submitButton.textContent = 'Submit task';
    updDiv.appendChild(submitButton);

    dropAreaDiv.appendChild(updDiv);

    return dropAreaDiv;
}

function cre8slider(titleText, id, fromValue, toValue, min, max) {
    const sectionDiv = DIV.cloneNode(true)
    const h6 = document.createElement('h6');
    h6.textContent = titleText;
    sectionDiv.appendChild(h6);

    const scoreRangeDiv = DIV.cloneNode(true)
    scoreRangeDiv.id = id;
    scoreRangeDiv.classList.add('dropfilt', 'selrang', 'show');
    const rangeContainerDiv = DIV.cloneNode(true)
    rangeContainerDiv.classList.add('range_container');

    const slidersControlDiv = DIV.cloneNode(true)
    slidersControlDiv.classList.add('sliders_control');

    const fromSlider = document.createElement('input');
    fromSlider.id = 'fromSlider';
    fromSlider.type = 'range';
    fromSlider.value = fromValue;
    fromSlider.min = '0';
    fromSlider.max = '100';
    slidersControlDiv.appendChild(fromSlider);

    if (toValue) {
        const toSlider = document.createElement('input');
        toSlider.id = 'toSlider';
        toSlider.type = 'range';
        toSlider.value = toValue;
        toSlider.min = '0';
        toSlider.max = '100';
        slidersControlDiv.appendChild(toSlider);
    }

    rangeContainerDiv.appendChild(slidersControlDiv);
    scoreRangeDiv.appendChild(rangeContainerDiv);

    if (min && max) {
        const formControlDiv = DIV.cloneNode(true)
        formControlDiv.classList.add('form_control');
        const formControlContainerDiv = DIV.cloneNode(true)
        formControlContainerDiv.classList.add('form_control_container');

        const input = document.createElement('input');
        input.type = 'number';
        input.id = 'toInpudt';
        input.value = '25';
        input.min = min;
        input.max = max;

        formControlContainerDiv.appendChild(input);
        formControlDiv.appendChild(formControlContainerDiv);
        rangeContainerDiv.appendChild(formControlDiv);
    }

    sectionDiv.appendChild(scoreRangeDiv);
    return sectionDiv;
}

function createGenderSection() {
    const genderDiv = DIV.cloneNode(true)
    const h6 = document.createElement('h6');
    h6.textContent = 'Gender';
    genderDiv.appendChild(h6);

    const pilWrDiv = DIV.cloneNode(true)
    pilWrDiv.id = 'pGOp';
    pilWrDiv.classList.add('pilWr', 'y');
    pilWrDiv.style.width = '330px';

    const pilBgDiv = DIV.cloneNode(true)
    pilBgDiv.classList.add('pilBg', 'pointer');
    pilWrDiv.appendChild(pilBgDiv);

    ['Rh', 'Dh', 'Hh'].forEach((id, index) => {
        const pilItDiv = DIV.cloneNode(true)
        pilItDiv.id = id;
        pilItDiv.classList.add('pilIt', 'pointer');
        pilItDiv.textContent = ['Male', 'Female', 'All'][index];
        pilWrDiv.appendChild(pilItDiv);
    });

    genderDiv.appendChild(pilWrDiv);
    return genderDiv;
}





function generateDark() {
	let divZZ = DIV.cloneNode(true)
	divZZ.id='ZZ'
	divZZ.innerHTML=
	`<div id="panel2a" class="dn">
        <p>Scan this QR code and copy down this</p>
        <p>If you lose this secret, you will need to contact support and pass more sophisticated authentication to regain access to your account.</p>
        <svg id="QRa" xmlns="http://www.w3.org/2000/svg" xml:space="preserve" viewBox="0 0 33 33" style="width: 330px;">
          <rect x="0.5" y="0.5" width="6" height="6" fill="white" stroke-width="1" stroke="black" stroke-align="outer" />
          <rect x="2" y="2" width="3" height="3" />
          <rect x="26.5" y="0.5" width="6" height="6" fill="white" stroke-width="1" stroke="black" stroke-align="outer" />
          <rect x="28" y="2" width="3" height="3" />
          <rect x="0.5" y="26.5" width="6" height="6" fill="white" stroke-width="1" stroke="black" stroke-align="outer" />
          <rect x="2" y="28" width="3" height="3" />
          <rect x="26" y="26" width="7" height="7" />
        </svg>
        <button>Next</button>
      </div>
      <div id="dropArea" class="y z">
        <div style="width: 500px;">
          <form class="my-form">
            <p id="ptxt">Upload pictures</p>
            <input type="file" id="fileElem" multiple accept=".jpg, .jpeg, .png, .webp, .heif" onchange="handleFiles(this.files)">
            <label id="UpB" class="dashed-repeating-gradient button" for="fileElem">
            <span>Drop your image here, or browse</span><span
            style="
                display: block;
    font-size: 10px;
    color: #999;
    ">Supports JPG, JPEG, PNG, WEBP, HEIF</span></label>
            
          </form>
          <p class="dn">Implement a dropdown function for the gallery that would include a caret. This is so we can hide the images if the user believes it to be annoying. Also allow for deletion and addition of images. No make this a gallery like instagram, but where you can go through a total filelevel view</p>
          <img id="prvIm" style="width:500px">
          <div id="upgal" class="GaL y"></div>
        </div>
        <div id="Upd" class="dn" style="width:400px;padding: 0 24px;box-sizing: border-box;">
          <h4 style="margin:0;padding:24px 0 12px">Task preferences</h4>
          <div>
            <h6>Age</h6>
            <div class="">
              <div id="scoreRangex" class="dropfilt selrang show">
                <div class="range_container">
                  <div class="sliders_control">
                    <input id="fromSlider" type="range" value="10" min="0" max="100"/>
                    <input id="toSlider" type="range" value="40" min="0" max="100"/>
                  </div>
                </div>
              </div>
            </div>
          </div>
          <div>
            <h6>Gender</h6>
            <div id="pGOp" class="pilWr y" style="width: 330px;">
              <div class="pilBg pointer"></div>
              <div id="Rh" class="pilIt pointer">Male</div>
              <div id="Dh" class="pilIt pointer">Female</div>
              <div id="Hh" class="pilIt pointer">All</div>
            </div>
          </div>
          <div>
            <h6># votes / image</h6>
            <div class=" ">
              <div id="scoreRang" class="dropfilt selrang show">
                <div class="range_container">
                  <div class="sliders_control">
                    <input id="numSlider" type="range" value="25" min="1" max="100"/>
                  </div>
                  <div class="form_control">
                    <div class="form_control_container">
                      <input type="number" id="toInpudt" value="25" min="1" max="10000"/>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
          <span class="F12 T16">Credits needed</span><br><span>10 images x 10 votes/image = 100 credits</span>
          <button style="width: 100%;margin: 2em 0 0;" class="btn blue">Submit task</button>
        </div>
      </div>

      <div class="abs dn" style=" background: white;width: 700px;display: none;" id="REPa">
        <h3>Are you sure you want to report this image?</h3>
        <p>Images can be reported for being spammy, pornographic, or harassing.</p>
        <button id="" class="btn alt">Submit</button>
      </div>
      <div id="buyCredData" class="box-layout abs" style="display:none">
        <div id="z40c" class="mt11 pt11 buy-button">
          <div class="credit-buy">
            <a href="/" target="_blank" class="w48p price v mat buy w5 tr btn-primary f17"><span>$5</span></a>
            <div class="quantity v w120p w6">50 Credits</div>
          </div>
        </div>
        <div id="z100c" class="mt11 pt11 buy-button">
          <div class="credit-buy">
            <a href="/" target="_blank" class="w48p price v mat buy w5 tr btn-primary f17"><span>$9</span></a>
            <div class="quantity v w120p w6">100 Credits</div>
            <div class="disc">(10% discount)</div>
          </div>
        </div>
        <div id="z250c" class="mt11 pt11 buy-button">
          <div class="credit-buy">
            <a href="/" target="_blank" class="w48p price v mat buy w5 tr btn-primary f17"><span>$13</span></a>
            <div class="quantity v w120p w6">150 Credits</div>
            <div class="disc v w120p w6">(13% discount)</div>
          </div>
        </div>
        <div id="z500c" class="mt11 pt11 buy-button">
          <div class="credit-buy">
            <a href="/" target="_blank" class="w48p price v mat buy w5 tr btn-primary f17"><span>$16</span></a>
            <div class="quantity v w120p w6">200 Credits</div>
            <div class="disc v w120p w6">(20% discount)</div>
          </div>
        </div>
        <div class="dn">
          <h2>Checkout</h2>
          <div>
            <input id="CCcodea" type="text">
            <input id="CCexpa" type="text">
            <input id="CCcvva" type="number">
          </div>
        </div>
      </div>`
    return divZZ
}



ZZ=generateDark()
document.body.appendChild(ZZ);


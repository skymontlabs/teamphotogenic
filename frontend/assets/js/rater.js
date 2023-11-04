function getRates() {
  let divCa = DYZ.cloneNode(true)
  divCa.id = 'Ca';

  let btnBR = BTN.cloneNode(true)
  btnBR.className='btn BR'
  btnBR.id='R0'

//https://stackoverflow.com/questions/4212909/can-css-force-a-line-break-after-each-word-in-an-element
  let btnB1=btnBR.cloneNode(true)
  btnB1.id='R1'
  let btnB2=btnBR.cloneNode(true)
  btnB2.id='R2'
  let btnB3=btnBR.cloneNode(true)
  btnB3.id='R3'
  let btnB4=btnBR.cloneNode(true)
  btnB4.id='R4'

  btnBR.innerHTML='😒<br>Eh'
  btnB1.innerHTML='😐<br>Decent'
  btnB2.innerHTML='😃<br>Great'
  btnB3.innerHTML='🤩<br>Stunning'
  btnB4.innerHTML='🤑<br>Brilliant'

  divCa.appendChild(btnBR)
  divCa.appendChild(btnB1)
  divCa.appendChild(btnB2)
  divCa.appendChild(btnB3)
  divCa.appendChild(btnB4)
  return divCa
}


function getUa() {
  let divUa = DIV.cloneNode(true)
  divUa.id = 'Ua';

  // Manually create and append each span
  let spanQa = SPN.cloneNode(true)
  spanQa.id = 'Qa';
  spanQa.className = 'BZ';
  spanQa.textContent = '😓 awkward';
  divUa.appendChild(spanQa);

  let spanQb = spanQa.cloneNode(true)
  spanQb.id = 'Qb';
  spanQb.textContent = '🫥 bad expression';
  divUa.appendChild(spanQb);

  let spanQc = spanQa.cloneNode(true)
  spanQc.id = 'Qc';
  spanQc.textContent = '🖼 bad framing';
  divUa.appendChild(spanQc);

  let spanQd = spanQa.cloneNode(true)
  spanQd.id = 'Qd';
  spanQd.textContent = '🍞 bland';
  divUa.appendChild(spanQd);

  let spanQe = spanQa.cloneNode(true)
  spanQe.id = 'Qe';
  spanQe.textContent = '🏟 distracting';
  divUa.appendChild(spanQe);

  let spanQf = spanQa.cloneNode(true)
  spanQf.id = 'Qf';
  spanQf.textContent = '💨 blurry';
  divUa.appendChild(spanQf);

  let spanQg = spanQa.cloneNode(true)
  spanQg.id = 'Qg';
  spanQg.textContent = '⚡️ bright';
  divUa.appendChild(spanQg);

  let spanQh = spanQa.cloneNode(true)
  spanQh.id = 'Qh';
  spanQh.textContent = '🚊 busy';
  divUa.appendChild(spanQh);

  let spanQi = spanQa.cloneNode(true)
  spanQi.id = 'Qi';
  spanQi.textContent = '🌈 colorful';
  divUa.appendChild(spanQi);

  let spanQj = spanQa.cloneNode(true)
  spanQj.id = 'Qj';
  spanQj.textContent = '🕶 cool';
  divUa.appendChild(spanQj);

  let spanQk = spanQa.cloneNode(true)
  spanQk.id = 'Qk';
  spanQk.textContent = '🌚 dark';
  divUa.appendChild(spanQk);

  let spanQl = spanQa.cloneNode(true)
  spanQl.id = 'Ql';
  spanQl.textContent = '😬 forced smile';
  divUa.appendChild(spanQl);

  let spanQm = spanQa.cloneNode(true)
  spanQm.id = 'Qm';
  spanQm.textContent = '🧂 grainy';
  divUa.appendChild(spanQm);

  let spanQn = spanQa.cloneNode(true)
  spanQn.id = 'Qn';
  spanQn.textContent = '🚨 overedited';
  divUa.appendChild(spanQn);

  let spanQo = spanQa.cloneNode(true)
  spanQo.id = 'Qo';
  spanQo.textContent = '🚶 poor posture';
  divUa.appendChild(spanQo);

  let spanQp = spanQa.cloneNode(true)
  spanQp.id = 'Qp';
  spanQp.textContent = '🔭 too far away';
  divUa.appendChild(spanQp);

  let spanQq = spanQa.cloneNode(true)
  spanQq.id = 'Qq';
  spanQq.textContent = '🔎 too close up';
  divUa.appendChild(spanQq);

  return divUa
}

function generateRatingBlock() {
    // Main containers
    const RIaDiv = document.createElement('div');
    RIaDiv.id = 'RIa';

    const RDaDiv = document.createElement('div');
    RDaDiv.id = 'RDa';

    // RIa child elements
    const RBaDiv = document.createElement('div');
    RBaDiv.id = 'RBa';
    RBaDiv.style.backgroundImage = "url('img/laurie.jpg')";
    RIaDiv.appendChild(RBaDiv);

    const imgElement = document.createElement('img');
    imgElement.src = "img/laurie.jpg";
    imgElement.alt = "Rating picture";
    RIaDiv.appendChild(imgElement);

    // RDa child elements - Rating
    const ratingSpan = document.createElement('span');
    ratingSpan.className = 'fwHeavy';
    ratingSpan.textContent = 'Rating*';
    RDaDiv.appendChild(ratingSpan);

/*
    const CaDiv = document.createElement('div');
    CaDiv.id = 'Ca';
    CaDiv.className = 'y z';

    const ratings = ['😒 Eh', '😐 Decent', '😃 Great', '🤩 Stunning', '🤑 Brilliant'];

    ratings.forEach((rating, index) => {
        const button = document.createElement('button');
        button.id = `R${index}`;
        button.className = 'btn BR';
        button.innerHTML = rating.replace(' ', '<br>');
        CaDiv.appendChild(button);
    });
*/
    RDaDiv.appendChild(getRates());

    // RDa child elements - Tags
    const tagsSpan = document.createElement('span');
    tagsSpan.className = 'fwHeavy';
    tagsSpan.textContent = 'Tags';
    RDaDiv.appendChild(tagsSpan);

/*
    const UaDiv = document.createElement('div');
    UaDiv.id = 'Ua';

    const tags = ['😓 awkward', '🫥 bad expression', '🖼 bad framing', '🍞 bland', '🏟 distracting', '💨 blurry',
        '⚡️ bright', '🚊 busy', '🌈 colorful', '🕶 cool', '🌚 dark', '😬 forced smile', '🧂 grainy', '🚨 overedited',
        '🚶 poor posture', '🔭 too far away', '🔎 too close up'];

    tags.forEach((tag, index) => {
        const span = document.createElement('span');
        span.id = `Q${String.fromCharCode(97 + index)}`;
        span.className = 'BZ';
        span.textContent = tag;
        UaDiv.appendChild(span);
    });
*/

    RDaDiv.appendChild(getUa());

    // Comment section
    const commentSpan = document.createElement('span');
    commentSpan.className = 'fwHeavy';
    commentSpan.textContent = 'Comment';
    RDaDiv.appendChild(commentSpan);

    const textareaElement = document.createElement('textarea');
    textareaElement.id = 'CMa';
    textareaElement.placeholder = "This picture seems ...";
    textareaElement.tabIndex = '-1';
    textareaElement.maxLength = '255';
    RDaDiv.appendChild(textareaElement);

    const actionDiv = document.createElement('div');
    actionDiv.className = 'y z rel';

    const dotsBtn = document.createElement('button');
    dotsBtn.id = 'Dmo';
    dotsBtn.className = 'dots btn';
    ['d0', 'd1', 'd2'].forEach(dotClass => {
        const span = document.createElement('span');
        span.className = dotClass;
        dotsBtn.appendChild(span);
    });

    actionDiv.appendChild(dotsBtn);

    const ulElement = document.createElement('ul');
    ulElement.id = 'rMor';
    ulElement.className = 'dropsort';
    const liElement = document.createElement('li');
    const reportSpan = document.createElement('span');
    reportSpan.id = 'Rpt';
    reportSpan.textContent = 'Report image';
    liElement.appendChild(reportSpan);
    ulElement.appendChild(liElement);
    actionDiv.appendChild(ulElement);

    const buttonsDiv = document.createElement('div');
    buttonsDiv.className = 'y';

    const skipBtn = document.createElement('button');
    skipBtn.id = 'Sk';
    skipBtn.className = 'pointer y btn';
    const skipSpan = document.createElement('span');
    skipSpan.className = 'f11';
    skipSpan.textContent = 'Skip';
    skipBtn.appendChild(skipSpan);
    buttonsDiv.appendChild(skipBtn);

    const submitBtn = document.createElement('button');
    submitBtn.id = 'Sm';
    submitBtn.className = 'pointer btn blue';
    const submitSpan = document.createElement('span');
    submitSpan.className = 'f11';
    submitSpan.textContent = 'Submit';
    submitBtn.appendChild(submitSpan);
    buttonsDiv.appendChild(submitBtn);

    actionDiv.appendChild(buttonsDiv);
    RDaDiv.appendChild(actionDiv);

    // Append the main containers to the body or any other parent element
    Mn.appendChild(RIaDiv);
    Mn.appendChild(RDaDiv);
}




function getRater() {
  Mn.id = 'Ra'
  Mn.className = 'y'
  generateRatingBlock()
}

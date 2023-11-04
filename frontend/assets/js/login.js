function genLogin() {
    Mn.id = 'Ya';
    Mn.children[0].className='x'

    const bgerDiv = document.createElement('div');
    bgerDiv.id = 'bger';
    Mn.appendChild(bgerDiv);

    const loginPanelDiv = document.createElement('div');
    loginPanelDiv.id = 'loginpanel';
    Mn.appendChild(loginPanelDiv);

    const h1 = document.createElement('h1');
    h1.style.fontSize = '20px';

    const signupTitleSpan = document.createElement('span');
    signupTitleSpan.id = 'signupTitle';
    signupTitleSpan.innerText = 'Sign up to get started';
    h1.appendChild(signupTitleSpan);

    const loginTitleSpan = document.createElement('span');
    loginTitleSpan.id = 'loginTitle';
    loginTitleSpan.innerText = 'Log in';
    h1.appendChild(loginTitleSpan);

    loginPanelDiv.appendChild(h1);

    const form = document.createElement('form');
    loginPanelDiv.appendChild(form);

    const orDiv = document.createElement('div');
    form.appendChild(orDiv);

    const emailLabel = document.createElement('label');
    emailLabel.innerText = 'Phone or Email';
    form.appendChild(emailLabel);

    const emailDiv = document.createElement('div');
    emailDiv.className = 'iS';
    emailDiv.style.width = '100%';
    form.appendChild(emailDiv);

    const emailInput = document.createElement('input');
    emailInput.id = 'emailSignup';
    emailInput.setAttribute('autocomplete', 'email');
    emailInput.name = 'email';
    emailInput.type = 'email';
    emailInput.placeholder = 'user@example.com';
    emailInput.style.width = '100%';
    emailInput.style.boxSizing = 'border-box';
    emailDiv.appendChild(emailInput);

/*
    const passwordDivWrapper = document.createElement('div');
    passwordDivWrapper.style.marginTop = '1em';
    form.appendChild(passwordDivWrapper);

    const passwordLabel = document.createElement('label');
    passwordLabel.innerText = 'Password';
    passwordDivWrapper.appendChild(passwordLabel);

    const passwordDiv = document.createElement('div');
    passwordDiv.className = 'iS';
    passwordDivWrapper.appendChild(passwordDiv);

    const passwordInput = document.createElement('input');
    passwordInput.id = 'passwordSignup';
    passwordInput.name = 'password';
    passwordInput.type = 'password';
    passwordInput.placeholder = 'Password';
    passwordInput.style.width = '100%';
    passwordInput.style.boxSizing = 'border-box';
    passwordDiv.appendChild(passwordInput);
*/

    const signupButton = document.createElement('button');
    signupButton.id = 'signupeq';
    signupButton.innerText = 'Next';
    loginPanelDiv.appendChild(signupButton);

    const footerDiv = document.createElement('div');
    footerDiv.style.width = '100%';
    loginPanelDiv.appendChild(footerDiv);

    const errorP = document.createElement('p');
    errorP.id = 'WrPa';
    errorP.className = 'meta red';
    errorP.innerText = 'Wrong password';
    footerDiv.appendChild(errorP);

    const termsDiv = document.createElement('div');
    termsDiv.className = 'PrPa';
    termsDiv.innerHTML = 'By signing up, you agree to our <a href="https://frame.io/terms/" target="_blank">Terms of Service</a> and <a href="https://frame.io/privacy" target="_blank">Privacy Policy.</a>';
    footerDiv.appendChild(termsDiv);

    const loginP = document.createElement('p');
    loginP.className = 'meta';
    loginP.innerHTML = 'Already have an account? <a href="/welcome">Log in.</a>';
    footerDiv.appendChild(loginP);

}


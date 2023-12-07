const slider = document.querySelector('.slider');
const prevButton = document.querySelector('.prev-button');
const nextButton = document.querySelector('.next-button');
const slides = Array.from(slider.querySelectorAll('img'));
const slideCount = slides.length;
let slideIndex = 0;

prevButton.addEventListener('click', () => {
  slideIndex = (slideIndex - 1 + slideCount) % slideCount;
  slide();
});

nextButton.addEventListener('click', () => {
  slideIndex = (slideIndex + 1) % slideCount;
  slide();
});

const slide = () => {
  const imageWidth = slider.clientWidth;
  const slideOffset = -slideIndex * imageWidth;
  slider.style.transform = `translateX(${slideOffset}px)`;
}

window.addEventListener('load', () => {
  slide();
});
var modals = document.querySelectorAll(".modal");
var triggers = document.querySelectorAll(".trigger");
var closeButtons = document.querySelectorAll(".close-button");

function toggleModal() {
    var modal = this.nextElementSibling;
    modal.classList.toggle("show-modal");
}

function windowOnClick(event) {
    modals.forEach(function (modal) {
        if (event.target === modal) {
            modal.classList.remove("show-modal");
        }
    });
}

triggers.forEach(function (trigger) {
    trigger.addEventListener("click", toggleModal);
});

closeButtons.forEach(function (closeButton) {
    closeButton.addEventListener("click", function () {
        var modal = this.closest(".modal");
        modal.classList.remove("show-modal");
    });
});

window.addEventListener("click", windowOnClick);
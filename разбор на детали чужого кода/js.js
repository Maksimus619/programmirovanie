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

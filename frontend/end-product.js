const initialData = {
    name: "Women's Mid Rise Skinny Jeans",
    categoryId: "100",
};

const maxNameLength = 50;
const validCategoryIds = [100, 101];

function initializePage() {
    document.getElementById(("name".value = initialData.name));
    const category = document.getElementById("category");
    const count = category.length;

    for (let i = 0; i < count; i++) {
        if (category[i].value === initialData.categoryId) {
            category.selectedIndex = i;
            break;
        }
    }
}

function getSelectedCategoryId() {
    const category = document.getElementById("category");
    const index = category.selectedIndex;
    if (index !== -1) {
        return category[index].value;
    }

    return "0";
}

function setErrorMessage(error) {
    const errorMessage = document.getElementById("errorMessage");
    errorMessage.innerText = error;
    errorMessage.style.display = error === "" ? "none" : "";
}

function onClickSave() {
    let errorMessage = "";
    const errorMessagePointer = Module._malloc(256);

    const name = document.getElementById("name").value;
    const categoryId = getSelectedCategoryId();

    if (
        !validateName(name, errorMessagePointer) ||
        !validateCategory(categoryId, errorMessagePointer)
    ) {
        errorMessage = Module.UTF8ToString(errorMessagePointer);
    }

    Module._free(errorMessagePointer);

    setErrorMessage(errorMessage);
    if (errorMessage === "") {
        console.log("no issues");
    }
}

function validateName(name, errorMessagePointer) {
    const isValid = Module.ccall(
        "ValidateName",
        "number",
        ["string", "number", "number"],
        [name, maxNameLength, errorMessagePointer]
    );
    return isValid === 1;
}

function validateCategory(categoryId, errorMessagePointer) {
    const arrayLength = validCategoryIds.length;
    const bytesPerElement = Module.HEAP32.BYTES_PER_ELEMENT;
    const arrayPointer = Module._malloc((arrayLength * bytesPerElement));

    Module.HEAP32.set(validCategoryIds, (arrayPointer / bytesPerElement));

    const isValid = Module.ccall('ValidateCategory', 'number', ['string', 'number', 'number', 'number'], [categoryId, arrayPointer, arrayLength, errorMessagePointer]);

    Module._free(arrayPointer);
    return isValid === 1;
}
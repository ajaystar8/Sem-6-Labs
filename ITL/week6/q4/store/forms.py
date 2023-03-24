from django import forms


class ShoppingForm(forms.Form):
    # radio buttons
    brand = forms.ChoiceField(widget=forms.RadioSelect, choices=[(
        'HP', 'HP'), ('Nokia', 'Nokia'), ('Samsung', 'Samsung'), ('Motorola', 'Motorola'), ('Apple', 'Apple')])
    # checkboxes
    laptop = forms.BooleanField(widget=forms.CheckboxInput(), required=False)
    mobile = forms.BooleanField(widget=forms.CheckboxInput(), required=False)
    # textbox
    quantity = forms.CharField(max_length=5)

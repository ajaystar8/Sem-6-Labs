from django import forms


class CarInfoForm(forms.Form):
    carManufacturer = forms.ChoiceField(
        choices=[('VolksVagen', 'VW'), ('Mercedes', 'Mercedes'), ('BMW', 'BMW')])
    carModel = forms.CharField()

from django import forms


class StudentInfoForm(forms.Form):
    name = forms.CharField(max_length=100)
    roll = forms.CharField(max_length=3)
    subject = forms.ChoiceField(
        choices=[('phy', 'Physics'), ('chem', 'Chemistry'), ('math', 'Maths')])

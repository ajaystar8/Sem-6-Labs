from django.shortcuts import render
from store.forms import ShoppingForm

# Create your views here.


def shop(request):
    form = ShoppingForm()
    return render(request, 'shop.html', {'form': form})


def bill(request):
    if request.method == "POST":
        shop_info = ShoppingForm(request.POST)
        if shop_info.is_valid():
            brand = shop_info.cleaned_data['brand']
            laptop = shop_info.cleaned_data['laptop']
            mobile = shop_info.cleaned_data['mobile']
            quantity = shop_info.cleaned_data['quantity']
        if laptop == 1:
            bill = None
            nos = int(quantity)
            if brand == 'HP':
                bill = nos*50000
            elif brand == 'Nokia':
                bill = nos*60000
            elif brand == 'Samsung':
                bill = nos*70000
            elif brand == 'Motorola':
                bill = nos*80000
            elif brand == 'Apple':
                bill = nos*90000
            return render(request, 'bill.html', {'brand': brand, 'item': "Laptop", 'quantity': quantity, 'bill': str(bill)})
        elif mobile == 1:
            bill = None
            nos = int(quantity)
            if brand == 'HP':
                bill = nos*10000
            elif brand == 'Nokia':
                bill = nos*20000
            elif brand == 'Samsung':
                bill = nos*30000
            elif brand == 'Motorola':
                bill = nos*40000
            elif brand == 'Apple':
                bill = nos*50000
            return render(request, 'bill.html', {'brand': brand, 'item': "Mobile", 'quantity': quantity, 'bill': str(bill)})

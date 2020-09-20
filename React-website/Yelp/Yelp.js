const apiKey = "Xy5JNGVIOhQijp6mBouqcSOWjwjQY-hhQ7XsbCmiSMgD6yRMvtRxpHnqHMdnXEHvVni0nD-FVH2zRoM8aV3lFq00ON0fOuGuziXbA8vEqFp9_1BUSqGcdCuKpU1mX3Yx";
const clientId = "ws1wpiPrwZ2H6WXtgD6yCg";

const yelp = {
    searchYelp(term, location, sortBy) {
        return fetch('https://cors-anywhere.herokuapp.com/https://api.yelp.com/v3/businesses/search?term=${term}&location=${location}&sort_by=${sortBy}',
        {
            headers: {
                Authorization: 'Bearer ${apiKey}'
            }
        }).then(response => {
            return response.json();
        }).then(jsonResponse => {
            if (jsonResponse.businesses) {
                return jsonResponse.businesses.map((business) => {
                    console.log(business);
                    return {
                        id: business.id,
                        imageSrc: business.image_url,
                        name: business.name,
                        address: business.location.address1,
                        city: business.location.city,
                        state: business.location.state,
                        zipcode: business.location.zip_code,
                        category: business.categories[0].title,
                        rating: business.rating,
                        reviewCount: business.review_count,
                    }
                });
            }})
    }
}
export default yelp;

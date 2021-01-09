using Books_CRUD.Models;
using Books_CRUD.Models.Database;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Books_CRUD.Controllers
{
    public class BookController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Book
        public ActionResult Index()
        {
            List<Book> books = db.Books.ToList();
            return View(books);
        }

        /*Creati o actiune noua cu un parametru id unde view-ul afiseaza detaliile cartii care are acel numar
        drept BookId. In view-ul corespunzator actiunii ce enumera toate cartile, creati cu Razor pentru
        fiecare carte un link catre pagina cu detalii.*/

        public ActionResult Details(int? id)
        {
            if(id.HasValue)
            {
                Book book = db.Books.Find(id);
                if(book != null)
                {
                    return View(book);
                }
                return HttpNotFound("Could not find the book with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        /*Creati o clasa noua numita Publisher. Implementati, pe rand, relatii one-to-one, many-to-many, one-tomany intre ea si Book. 
         * Examinati structura bazei de date in Server Explorer.*/

    }
}
using Books.Models;
using Books.ViewModels;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Books.Controllers
{
    public class BooksController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Books
        //Read
        public ActionResult Index()
        {
            List<Book> books = db.Books.ToList();
            ViewBag.Books = books;

            return View();
        }

        //Read
        public ActionResult Details(int? id)
        {
            if(id.HasValue)
            {
                Book book = db.Books.Find(id);
                if(book != null)
                {
                    return View(book);
                }
                else
                {
                    return HttpNotFound("No book having this id");
                }
            }
            return RedirectToAction("Index");
        }

        //Create
        //pentru create avem 2 actiuni: una get si una post
        [HttpGet]
        public ActionResult New()
        {
            //doar va afisa un view pe ecran(iar din post luam datele din acea pagina
            //de obicei numele e new sau create(nume sugestive)
            BookAndBookTypesViewModel b = new BookAndBookTypesViewModel();
            b.Book = new Book();
            b.BookTypes = GetAllBookTypes();
            return View(b);
        }

        [HttpPost]
        public ActionResult New(BookAndBookTypesViewModel bookRequest)
        {
            //ia datele din formular si le pune in baza de date
            try
            {
                if(ModelState.IsValid)
                {
                    //verifica daca model binding a avut loc bine; 
                    //nu e valid daca nu se respecta validarile din model
                    //campul publisher e obligatoriu. Punem o varianta implicita
                    bookRequest.Book.Publisher = db.Publishers.FirstOrDefault(p => p.PublisherId.Equals(1));
                    db.Books.Add(bookRequest.Book);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                //daca nu se respecta validarile vrem sa vedem mesaj de eroare, deci ramanem pe aceeasi pagina
                bookRequest.BookTypes = GetAllBookTypes();
                return View(bookRequest);
            }
            catch(Exception e)
            {
                //atunci cand apare o eroare vrem sa ramanem pe pagina formularului
                return View(bookRequest);
            }
        }

        //Update
        public ActionResult Edit(int? id)
        {
            if(id.HasValue)
            {
                Book b = db.Books.Find(id);
                if (b == null)
                {
                    return HttpNotFound("The book does not exist in the database");
                }
                BookAndBookTypesViewModel bookViewModel = new BookAndBookTypesViewModel();
                bookViewModel.Book = b;
                bookViewModel.BookTypes = GetAllBookTypes();
                return View(bookViewModel);
            }
            return HttpNotFound("Missing id parameter");
        }

         [HttpPut] //!!!!!!!ATENTIE E DE TIP PUT
         public ActionResult Edit(int id, BookAndBookTypesViewModel bookRequest)
         {
            //trebuie sa ne memoreze id-ul
             try
             {
                 if(ModelState.IsValid)
                 {
                     //include face join intre book si publisher(eager loading); vrem sa ne asiguram ca book.Publisher e completat
                     //cauta cartea cu id-ul id
                     Book book = db.Books.Include("Publisher")
                                 .SingleOrDefault(b => b.BookId.Equals(id));
                     if (TryUpdateModel(book))
                     {
                         book.Title = bookRequest.Book.Title;
                         book.Author = bookRequest.Book.Author;
                         book.Summary = bookRequest.Book.Summary;
                         book.BookTypeId = bookRequest.Book.BookTypeId;
                         db.SaveChanges();
                     }
                     return RedirectToAction("Index");
                 }
                //daca esueaza, vrem sa vedem erorile pe aceeasi pagina
                bookRequest.BookTypes = GetAllBookTypes();
                return View(bookRequest);
             }
             catch(Exception e)
             {
                 return View(bookRequest);
             }
         }

        //Delete
        [HttpPut]
        public ActionResult Delete(int? id)
        {
            if(id.HasValue)
            {
                Book b = db.Books.Find(id);
                if (b == null)
                {
                    return HttpNotFound("The book does not exist in the database");
                }
                db.Books.Remove(b);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return HttpNotFound("Missing id parameter");
        }

        [NonAction]
        public IEnumerable<BookType> GetAllBookTypes()
        {
            //formam o lista cu BookTypes extrase din baza de date
            var selectList = new List<BookType>();

            foreach(var cover in db.BookTypes.ToList())
            {
                //adaugam in dropdown list
                selectList.Add(new BookType
                {
                    BookTypeId = cover.BookTypeId,
                    Name = cover.Name
                });
            }
            return selectList;
        }


    }
}
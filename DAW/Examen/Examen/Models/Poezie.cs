using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Examen.Models
{
    public class Poezie
    {
        [Key]
        public int IdPoezie { get; set; }
        [Required]
        [MinLength(2, ErrorMessage = "Titlul trebuie sa aiba cel putin 2 caractere!"),
            MaxLength(60, ErrorMessage = "Titlul trebuie sa aiba cel mult 60 de caractere!")]
        public String Titlu { get; set; }
        [Required]
        [MinLength(2, ErrorMessage = "Autorul trebuie sa aiba cel putin 2 caractere!"),
            MaxLength(50, ErrorMessage = "Autorul trebuie sa aiba cel mult 50 de caractere!")]

        public String  Autor { get; set; }
        [Required]
        [RegularExpression(@"^[1-9]\d*$", ErrorMessage = "Numarul de strofe trebuie sa fie mai mare ca 0!")]
        public int NrStrofe { get; set; }
        
        [ForeignKey("Volum")]
        public int IdVolum { get; set; }
        public virtual Volum Volum { get; set; }
        
        [NotMapped]
        public IEnumerable<SelectListItem> ListaVolume { get; set; }

    }
}
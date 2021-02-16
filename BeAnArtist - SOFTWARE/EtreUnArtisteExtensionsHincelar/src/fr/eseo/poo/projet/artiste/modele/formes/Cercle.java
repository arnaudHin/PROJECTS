package fr.eseo.poo.projet.artiste.modele.formes;


import fr.eseo.poo.projet.artiste.modele.Coordonnees;


public class Cercle extends Ellipse{
	
	public Cercle(Coordonnees position, double taille) {
		super(position, taille, taille);
		this.setLargeur(taille);
		this.setHauteur(taille);
	}
	public Cercle(Coordonnees position){ 
		this(position, Forme.LARGEUR_PAR_DEFAUT); 
		}
	public Cercle(double taille) { 
		this(new Coordonnees(), taille); 
		}
	public Cercle() { 
		this(new Coordonnees(), Forme.LARGEUR_PAR_DEFAUT); 
		}

	public void setLargeur(double largeur){
		super.setLargeur(largeur); 
		if(largeur != this.getHauteur()) {
			this.setHauteur(largeur); }
		}
	
	public void setHauteur(double hauteur){ 
		super.setHauteur(hauteur); 
		if(hauteur != this.getLargeur()) {
			this.setLargeur(hauteur);}
	}	
	
	public double aire(){ 
		return 0.25*this.getLargeur()*this.getLargeur()*Forme.PI; 
		}
	public double perimetre(){ 
		return 2*Forme.PI*this.getLargeur()*0.5; 
		}	
	public boolean contient(Coordonnees coord) { 
		return super.contient(coord); 
		}	
}
